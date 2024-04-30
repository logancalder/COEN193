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

char EventNameString[PAPI_MAX_STR_LEN];

#define NUM_EVENTS 2
long long events[NUM_EVENTS] = {PAPI_TOT_CYC, PAPI_TOT_INS};

int getNumEvents()
{
    return NUM_EVENTS;
}

int initializePAPI(int &EventSet)
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

    for (int i = 0; i < NUM_EVENTS; i++)
    {
        PAPI_event_code_to_name(events[i], EventNameString);

        // Add event to EventSet
        if (PAPI_add_event(EventSet, events[i]) != PAPI_OK)
        {
            std::cerr << "PAPI event add failed for event: " << EventNameString << std::endl;
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

void stopPAPI(long long *values, int EventSet, long long *avgValues, int trialNumber)
{
    // Stop counting events
    if (PAPI_stop(EventSet, values) != PAPI_OK)
    {
        std::cout << "PAPI stop failed!" << std::endl;
        return;
    }

    for (int i; i < NUM_EVENTS; i++)
    {
        avgValues[i + (trialNumber * NUM_EVENTS)] += values[i];
    }
}

void cleanUpPAPI(int EventSet, long long *avgValues, int numTrials)
{
    PAPI_cleanup_eventset(EventSet);
    PAPI_destroy_eventset(&EventSet);
    PAPI_shutdown();

    // FILE WRITING PER TRIAL VALUES (should be outside the loop if you're measuring multiple iterations)
    std::string filepath = "papi_results/" + fileName + ".csv";
    std::ofstream file(filepath, std::ios::app);

    if (!file.is_open())
    {
        std::cout << "Error opening file: " << filepath << std::endl;
    }

    file << "Event Name,Value\n"; // Write column headers of csv file

    std::cout << "\n-------------------------------- OUTPUT ----------------------------------" << std::endl;

    for (int i = 0; i < numTrials * NUM_EVENTS; i++) // Average data
    {
        avgValues[i] /= numTrials;
    }

    for (int i = 0; i < NUM_EVENTS; i++)
    {
        std::cout << EventNameString << "\t";
        file << EventNameString;

        for (int j = 0; j < numTrials; j++)
        {
            if (PAPI_event_code_to_name(events[i], EventNameString) != PAPI_OK)
            {
                std::cerr << "PAPI event code to name conversion failed for event: " << events[j] << std::endl;
                return;
            }

            std::cout << avgValues[i + (j * NUM_EVENTS)] << std::endl;

            file << "," << avgValues[i + (j * NUM_EVENTS)]; // Write data into file
        }

        std::cout << std::endl;
    }

    file.close();
}

#endif // DA_H
