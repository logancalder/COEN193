#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <papi.h>
#include <iomanip>
#include "matmul.h"
#include "externals.h"
#include "perfcounters.h"

std::vector<std::string> eventNames;
std::string fileName = getCurrentDateTimeString();

char EventNameString[PAPI_MAX_STR_LEN];
int EventCode = PAPI_NULL;

int numEvents = 0;
std::vector<long long> eventCodes;
std::string line;

void readInput()
{
    // Open the input file
    std::ifstream inputFile("PAPI_input.txt");

    if (!inputFile.is_open())
    {
        std::cerr << "Error: Failed to open the input file.\n";
        return;
    }

    while (std::getline(inputFile, line))
    {
        numEvents++;
        eventNames.push_back(line);
        const char *lineChar = line.c_str();

        if (PAPI_event_name_to_code(lineChar, &EventCode) != PAPI_OK)
            std::cerr << "Error: Could not find event name.\n";

        eventCodes.push_back(EventCode);
    }

    inputFile.close();

    std::cout << "Lines read from the file:\n";
    for (const auto &event : eventNames)
    {
        std::cout << event << '\n';
    }

    return;
}

int getNumEvents()
{
    return numEvents;
}

int initializePAPI(int &EventSet)
{
    std::cout << "Initializing PAPI..." << std::endl;

    if (PAPI_library_init(PAPI_VER_CURRENT) != PAPI_VER_CURRENT)
    {
        std::cerr << "PAPI initialization failed!" << std::endl;
        return -1;
    }

    std::cout << "PAPI Version: " << PAPI_VERSION << std::endl;

    if (PAPI_create_eventset(&EventSet) != PAPI_OK)
    {
        std::cerr << "PAPI event creation failed!" << std::endl;
        return -1;
    }

    std::cout << "PAPI EventSet created\nAdding events..." << std::endl;

    for (int i = 0; i < numEvents; i++)
    {
        PAPI_event_code_to_name(events[i], EventNameString);

        // Add event to EventSet
        if (PAPI_add_event(EventSet, events[i]) != PAPI_OK)
        {
            std::cerr << "PAPI event add failed for event: " << EventNameString << std::endl;
            return -1;
        }
    }

    std::cout << "Starting PAPI..." << std::endl;
    // Start counting events
    if (PAPI_start(EventSet) != PAPI_OK)
    {
        std::cerr << "PAPI start failed!" << std::endl;
        return -1;
    }

    return EventSet;
}

void stopPAPI(long long *values, int trialNumber, int EventSet)
{
    std::cout << "Stopping PAPI..." << std::endl;
    // Stop counting events
    if (PAPI_stop(EventSet, values) != PAPI_OK)
    {
        std::cout << "PAPI stop failed!" << std::endl;
        return;
    }

    // FILE WRITING PER TRIAL VALUES (should be outside the loop if you're measuring multiple iterations)
    std::string filepath = "papi_results/" + fileName + ".txt";
    std::ofstream file(filepath, std::ios::app);

    if (!file.is_open())
    {
        std::cout << "Error opening file: " << filepath << std::endl;
    }

    for (int i = 0; i < numEvents; i++)
    {
        if (PAPI_event_code_to_name(events[i], EventNameString) != PAPI_OK)
        {
            std::cerr << "PAPI event code to name conversion failed for event: " << events[i] << std::endl;
            return;
        }
        file << EventNameString << ":\t" << values[i] << std::endl; // Write data into file
    }

    file.close();

    // Clean up PAPI

    std::cout << "Cleaning up PAPI..." << std::endl;
    PAPI_cleanup_eventset(EventSet);
    PAPI_destroy_eventset(&EventSet);
    PAPI_shutdown();
}
