#ifndef DA_H
#define DA_H
#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <papi.h>
#include <iomanip>
#include "matmul.h"
#include "externals.h"

std::string fileName = getCurrentDateTimeString();

#define events_path "papi_events.txt"

void initializeCompletion()
{
    std::cout << "Progress: [          ] 0%\r";
    std::cout.flush();
}

void displayCompletion(float counter, float total_calculations)
{
    // Percentage progress bar
    std::cout << "Progress: [";
    for (int j = 0; j < counter; ++j)
    {
        std::cout << "#";
    }
    for (int j = counter; j < total_calculations; ++j)
    {
        std::cout << " ";
    }
    std::cout << "] " << (counter * 100 / total_calculations) << "%\r";
    std::cout.flush(); // Flush the output to ensure it's displayed immediately
}

int get_events(std::vector<std::string> &events)
{
    // Native events
    std::ifstream events_file(events_path);
    if (!events_file.is_open())
    {
        std::cerr << "Unable to read native events" << std::endl;
        exit(1);
    }

    std::string line;
    while (getline(events_file, line))
    {
        if (!line.empty())
        {
            events.push_back(line);
        }
    }

    events_file.close();

    return events.size();
}

int initializePAPI(int &EventSet, std::vector<std::string> events)
{
    if (PAPI_library_init(PAPI_VER_CURRENT) != PAPI_VER_CURRENT)
    {
        std::cerr << "PAPI initialization failed!" << std::endl;
        return -1;
    }

    if (PAPI_create_eventset(&EventSet) != PAPI_OK)
    {
        std::cerr << "PAPI event creation failed!" << std::endl;
        return -1;
    }

    for (int i = 0; i < events.size(); i++)
    {
        // Add event to EventSet
        if (PAPI_add_named_event(EventSet, events.at(i).c_str()) != PAPI_OK)
        {
            std::cerr << "PAPI event add failed for event: " << events.at(i) << std::endl;
            return -1;
        }
    }

    return EventSet;
}

void startPAPI(int EventSet)
{
    // Start counting events
    if (PAPI_start(EventSet) != PAPI_OK)
    {
        std::cerr << "PAPI start failed!" << std::endl;
        return;
    }
}

void stopPAPI(long long *values, int EventSet, long long *avgValues, int trialNumber, int num_events, float counter, float total_calculations)
{
    // Stop counting events
    if (PAPI_stop(EventSet, values) != PAPI_OK)
    {
        std::cout << "PAPI stop failed!" << std::endl;
        return;
    }

    for (int i; i < num_events; i++)
    {
        avgValues[i + (trialNumber * num_events)] += values[i];
    }

    displayCompletion(counter, total_calculations);
}

void cleanUpPAPI(int EventSet, long long *avgValues, int numTrials, int num_events, std::vector<std::string> events)
{
    PAPI_cleanup_eventset(EventSet);
    PAPI_destroy_eventset(&EventSet);
    PAPI_shutdown();

    std::cout << "Progress: [##########] 100%" << std::endl; // Progress bar completion

    // FILE WRITING PER TRIAL VALUES (should be outside the loop if you're measuring multiple iterations)
    std::string filepath = "papi_results/" + fileName + ".csv";
    std::ofstream file(filepath, std::ios::app);

    if (!file.is_open())
    {
        std::cout << "Error opening file: " << filepath << std::endl;
    }

    std::cout << "\n-------------------------------- OUTPUT ----------------------------------" << std::endl;

    for (int i = 0; i < numTrials * num_events; i++) // Average data
    {
        avgValues[i] /= numTrials;
    }

    file << "Event Name"; // Write column headers of csv file

    for (int i = 0; i < numTrials; i++)
    {
        file << "," << i + 1 << " Threads";
    }

    for (int i = 0; i < num_events; i++)
    {
        std::cout << events.at(i) << std::endl;
        file << "\n"
             << events.at(i);

        for (int j = 0; j < numTrials; j++)
        {
            std::cout << avgValues[i + (j * num_events)] << std::endl;

            file << "," << avgValues[i + (j * num_events)]; // Write data into file
        }

        std::cout << std::endl;
    }

    file.close();
}

#endif // DA_H
