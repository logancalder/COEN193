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

void displayCompletion(float counter, float totalRuns)
{
    std::cout << "Progress: [";
    for (int k = 0; k < (counter / totalRuns) * 10; k++)
    {
        std::cout << "#";
    }
    for (int k = 0; k < 10 - (counter / totalRuns * 10); k++)
    {
        std::cout << " ";
    }
    std::cout << "] " << (counter / totalRuns * 100) << "%\r";
    std::cout.flush();
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

void initializePAPI(int *EventSet, std::string event)
{

#pragma omp parallel
    {
        int threadID = omp_get_thread_num();
        EventSet[threadID] = PAPI_NULL;
        PAPI_thread_init(pthread_self);

        if (PAPI_create_eventset(&EventSet[threadID]) != PAPI_OK)
        {
            std::cerr << "PAPI event creation failed!" << std::endl;
        }

        // Add event to EventSet
        if (PAPI_add_named_event(EventSet[threadID], event.c_str()) != PAPI_OK)
        {
            std::cerr << "PAPI event add failed for event: " << event.c_str() << std::endl;
        }
    }
}

void startPAPI(int *EventSet)
{
#pragma omp parallel
    {
        int threadID = omp_get_thread_num();
        // Start counting events
        if (PAPI_start(EventSet[threadID]) != PAPI_OK)
        {
            std::cerr << "PAPI start failed!" << std::endl;
        }
    }
}

void stopPAPI(long long *values, int *EventSet, long long *avgValues, int currentEventNumber, float counter, float totalRuns, int numEvents)
{
#pragma omp parallel
    {
        int threadID = omp_get_thread_num();
        // Stop counting events
        if (PAPI_stop(EventSet[threadID], &values[threadID]) != PAPI_OK)
        {
            std::cout << "PAPI stop failed!" << std::endl;
        }
        PAPI_cleanup_eventset(EventSet[threadID]);
        PAPI_destroy_eventset(&EventSet[threadID]);
    }

    for (int i = 0; i < omp_get_max_threads(); i++)
    {
        avgValues[currentEventNumber] += values[i];
    }

    displayCompletion(counter, numEvents);
}

void cleanUpPAPI(int *EventSet, long long *avgValues, float averageRuntime, int num_events, std::vector<std::string> events, float totalRuns, string name)
{
#pragma omp parallel
    {
        int threadID = omp_get_thread_num();
    }

    std::cout << "Progress: [##########] 100% Completed" << std::endl; // Progress bar completion

    // FILE WRITING PER TRIAL VALUES (should be outside the loop if you're measuring multiple iterations)
    std::string filepath = "papi_results/" + name + "_" + fileName + ".csv";
    std::ofstream file(filepath, std::ios::app);

    if (!file.is_open())
    {
        std::cout << "Error opening file: " << filepath << std::endl;
    }

    std::cout << "\n-------------------------------- OUTPUT ----------------------------------" << std::endl;

    file << "Event Name"; // Write column headers of csv file

    // Write PAPI event data to file
    // ==================================================================================

    for (int i = 0; i < num_events; i++)
    {
        avgValues[i] /= totalRuns;

        std::cout << events.at(i) << std::endl;
        std::cout << avgValues[i] << std::endl;

        file << "\n"
             << events.at(i);

        file << "," << avgValues[i];

        std::cout << std::endl;
    }

    // Write runtime to file
    // ==================================================================================

    averageRuntime /= totalRuns;

    std::cout << "RUNTIME\n"
              << averageRuntime << std::endl;

    file << "\n"
         << "RUNTIME";

    file << "," << averageRuntime; // Write data into file

    std::cout << std::endl;

    file.close();
}

#endif // DA_H

