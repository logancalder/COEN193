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

int numEvents = 0;

std::string fileName = getCurrentDateTimeString();

long long events[2] = {PAPI_TOT_CYC, PAPI_TOT_INS};

int returnNumEventsPAPI()
{
    return numEvents;
}

int initializePAPI(int EventSet)
{
    std::cout << "Initializing PAPI..." << std::endl;
    // PAPI Initialization (move outside the loop)
    if (PAPI_library_init(PAPI_VER_CURRENT) != PAPI_VER_CURRENT)
    {
        std::cerr << "PAPI initialization failed!" << std::endl;
        return -1;
    }

    std::cout << "PAPI Version: " << PAPI_VERSION << std::endl;
    // Create EventSet
    if (PAPI_create_eventset(&EventSet) != PAPI_OK)
    {
        std::cerr << "PAPI event creation failed!" << std::endl;
        return -1;
    }

    std::cout << "PAPI EventSet created" << std::endl;

    for (int i = 0; i < 2; i++)
    {
        std::cout << "Adding event: " << events[i] << std::endl;

        // Add event to EventSet
        if (PAPI_add_event(EventSet, events[i]) != PAPI_OK)
        {
            std::cerr << "PAPI event add failed for event: " << events[i] << std::endl;
            return -1;
        }
        std::cout << "Event added" << std::endl;
        numEvents++;
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

    if (trialNumber == 0)
        file << "TRIAL\tINST\t\tCYCL"; // Header

    file << trialNumber << "\t" << values[0] << "\t" << values[1] << std::endl; // Write data into file
    std::cout << "Stopping" << std::endl;
    file.close();

    // Clean up PAPI

    std::cout << "Cleaning up PAPI..." << std::endl;
    PAPI_cleanup_eventset(EventSet);
    PAPI_destroy_eventset(&EventSet);
    PAPI_shutdown();
}

#endif // DA_H
