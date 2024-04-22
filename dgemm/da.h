#ifndef DA_H
#define DA_H

#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include "da.h"

int EventSet = PAPI_NULL;

int numEvents = 0;

std::string fileName = getCurrentDateTimeString();

int returnNumEventsPAPI()
{
    return numEvents;
}

void initializePAPI(std::string inputFile)
{
    // PAPI Initialization (move outside the loop)
    if (PAPI_library_init(PAPI_VER_CURRENT) != PAPI_VER_CURRENT)
    {
        std::cerr << "PAPI initialization failed!" << std::endl;
        return;
    }

    // Create EventSet
    if (PAPI_create_eventset(&EventSet) != PAPI_OK)
    {
        std::cerr << "PAPI event creation failed!" << std::endl;
        return;
    }

    // Read events from input file
    std::ifstream input(inputFile);
    if (!input.is_open())
    {
        std::cerr << "Error opening file: " << inputFile << std::endl;
        return;
    }

    std::string event;
    while (std::getline(input, event))
    {
        // Convert event string to integer
        int eventCode = std::stoi(event);

        // Add event to EventSet
        if (PAPI_add_event(EventSet, eventCode) != PAPI_OK)
        {
            std::cerr << "PAPI event add failed for event: " << event << std::endl;
            return;
        }
        numEvents++;
    }

    input.close();
}

void startPAPI()
{
    // Start counting events
    if (PAPI_start(EventSet) != PAPI_OK)
    {
        std::cerr << "PAPI start failed!" << std::endl;
        return;
    }
}

void stopPAPI(long long *values, int trialNumber)
{
    // Stop counting events
    if (PAPI_stop(EventSet, values) != PAPI_OK)
    {
        std::cout << "PAPI stop failed!" << std::endl;
        return;

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

        if (trialNumber == 0)
            file << "TRIAL\tINST\t\tCYCL"; // Header

        file << trialNumber << "\t" << values[0] << "\t" << values[1] << std::endl; // Write data into file
        std::cout << "Stopping" << std::endl;
        file.close();
    }
}

// Cleanup

void cleanupPAPI(int EventSet)
{
    PAPI_cleanup_eventset(EventSet);
    PAPI_destroy_eventset(&EventSet);
    PAPI_shutdown();
}

#endif // DA_H