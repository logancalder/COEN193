#ifndef PERFCOUNTERS_H
#define PERFCOUNTERS_H
#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <papi.h>
#include <iomanip>
#include <vector>
#include "matmul.h"
#include "externals.h"

std::string fileName = getCurrentDateTimeString();

char EventNameString[PAPI_MAX_STR_LEN];

#define NUM_EVENTS 2
long long events[NUM_EVENTS] = {PAPI_TOT_CYC, PAPI_TOT_INS};

int getNumEvents();
int initializePAPI(int &EventSet);
void stopPAPI(long long *values, int trialNumber, int EventSet);

#endif // PERFCOUNTERS_H
