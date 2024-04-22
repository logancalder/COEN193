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

int EventSet = PAPI_NULL;

int numEvents = 0;

std::string fileName = getCurrentDateTimeString();

int returnNumEventsPAPI()
{
    return numEvents;
}

void initializePAPI(std::string inputFile)
{
    std::cout << "Initializing PAPI..." << std::endl;
    // PAPI Initialization (move outside the loop)
    if (PAPI_library_init(PAPI_VER_CURRENT) != PAPI_VER_CURRENT)
    {
        std::cerr << "PAPI initialization failed!" << std::endl;
        return;
    }

    std::cout << "PAPI Version: " << PAPI_VERSION << std::endl;
    // Create EventSet
    if (PAPI_create_eventset(&EventSet) != PAPI_OK)
    {
        std::cerr << "PAPI event creation failed!" << std::endl;
        return;
    }

    std::cout << "PAPI EventSet created" << std::endl;

    // Read events from input file
    std::ifstream input(inputFile);
    if (!input.is_open())
    {
        std::cerr << "Error opening file: " << inputFile << std::endl;
        return;
    }

    std::string event;
    std::cout << "Reading events from file..." << std::endl;

    while (std::getline(input, event))
    {
        std::cout << "Adding event: " << event << std::endl;
        // Convert event string to integer
        int eventCode = std::stoi(event);

        std::cout << "Event code: " << eventCode << std::endl;

        // Add event to EventSet
        if (PAPI_add_event(EventSet, eventCode) != PAPI_OK)
        {
            std::cerr << "PAPI event add failed for event: " << event << std::endl;
            return;
        }
        std::cout << "Event added" << std::endl;
        numEvents++;
    }

    input.close();
}

void startPAPI()
{
    printf("1");
    std::cout << "Starting PAPI..." << std::endl;
    // Start counting events
    if (PAPI_start(EventSet) != PAPI_OK)
    {
        std::cerr << "PAPI start failed!" << std::endl;
        return;
    }
}

void stopPAPI(long long *values, int trialNumber)
{
    std::cout << "Stopping PAPI..." << std::endl;
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
    std::cout << "Cleaning up PAPI..." << std::endl;
    PAPI_cleanup_eventset(EventSet);
    PAPI_destroy_eventset(&EventSet);
    PAPI_shutdown();
}

#endif // DA_H
