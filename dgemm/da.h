#ifndef DA_H
#define DA_H

#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <papi.h>
#include "externals.h"

void initializePAPI(std::string inputFile);
void startPAPI();
void stopPAPI(long long *values, int trialNumber);
void cleanupPAPI(int EventSet);
#endif // DA_H