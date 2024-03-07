#ifndef RECORDER
#define RECORDER

#include <chrono>
#include <iostream>
#include <random>
#include <fstream>

void record_matrix(int values[], int size, std::string file_name, int sq_size)
{

    // Calculate average runtime

    double sum = 0.0;
    for (int i = 0; i < size; ++i)
    {
        sum += values[i];
    }
    double average = sum / size;

    // File accessing

    std::string filepath = file_name;
    std::ofstream file(filepath, std::ios::app);

    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << filepath << std::endl;
        return;
    }

    file << sq_size << "x" << sq_size << "," << average << std::endl; // Write data into file
    file.close();

#endif