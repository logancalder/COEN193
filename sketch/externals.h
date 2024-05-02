#ifndef EXTERNALS
#define EXTERNALS

#include <iostream>
#include <ctime>
#include <sstream>

std::string getCurrentDateTimeString() {
    std::time_t currentTime = std::time(nullptr);
    std::tm* localTime = std::localtime(&currentTime);

    std::ostringstream oss;
    oss << "data-" << (localTime->tm_year + 1900) << "-" // Year is offset from 1900
        << (localTime->tm_mon + 1) << "-"                  // Month ranges from 0 to 11
        << localTime->tm_mday << "-"
        << localTime->tm_hour << "-" // Hour
        << localTime->tm_min << "-"  // Minute
        << localTime->tm_sec;        // Second

    return oss.str();
}

#endif
