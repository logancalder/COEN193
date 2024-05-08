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

// void displayCompletion(float counter, float total_calculations)
// {
//     std::cout << "Progress: [";
//     for (int k = 0; k < (counter / total_calculations) * 10; k++)
//     {
//         std::cout << "#";
//     }
//     for (int k = 0; k < 10 - (counter / total_calculations * 10); k++)
//     {
//         std::cout << " ";
//     }
//     std::cout << "] " << (counter / total_calculations * 100) << "%\r";
//     std::cout.flush();
// }

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

int initializePAPI(int &EventSet, std::string event)
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

    // Add event to EventSet
    if (PAPI_add_named_event(EventSet, event.c_str()) != PAPI_OK)
    {
        std::cerr << "PAPI event add failed for event: " << event.c_str() << std::endl;
        return -1;
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

void stopPAPI(long long *values, int EventSet, long long *avgValues, int currentEventNumber, float counter, float total_calculations)
{
    // Stop counting events
    if (PAPI_stop(EventSet, values) != PAPI_OK)
    {
        std::cout << "PAPI stop failed!" << std::endl;
        return;
    }

    std::cout << values[0] << std::endl; // Print the value of the event
    avgValues[currentEventNumber] += values[0];

    // displayCompletion(counter, total_calculations);
}

void cleanUpPAPI(int EventSet, long long *avgValues, int num_events, std::vector<std::string> events)
{
    PAPI_cleanup_eventset(EventSet);
    PAPI_destroy_eventset(&EventSet);
    PAPI_shutdown();

    // std::cout << "Progress: [##########] 100% Completed" << std::endl; // Progress bar completion

    // FILE WRITING PER TRIAL VALUES (should be outside the loop if you're measuring multiple iterations)
    std::string filepath = "papi_results/" + fileName + ".csv";
    std::ofstream file(filepath, std::ios::app);

    if (!file.is_open())
    {
        std::cout << "Error opening file: " << filepath << std::endl;
    }

    std::cout << "\n-------------------------------- OUTPUT ----------------------------------" << std::endl;

    file << "Event Name"; // Write column headers of csv file

    for (int i = 0; i < num_events; i++)
    {
        std::cout << "Event: " << events.at(i) << " average total: " << avgValues[i] << " num_events: " << std::endl;
        avgValues[i] /= num_events; // Average the data

        std::cout << events.at(i) << std::endl;
        std::cout << avgValues[i] << std::endl;

        file << "\n"
             << events.at(i);

        file << "," << avgValues[i]; // Write data into file

        std::cout << std::endl;
    }

    file.close();
}

#endif // DA_H
