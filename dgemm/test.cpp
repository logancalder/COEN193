#include <iostream>
#include <chrono>
#include <thread>

int main()
{
    // Print a line initially
    std::cout << "Progress: [          ] 0%\r";
    std::cout.flush(); // Make sure the output is flushed

    // Simulate a progress bar update
    for (int i = 0; i <= 10; ++i)
    {
        // Update the progress bar
        std::cout << "Progress: [";
        for (int j = 0; j < i; ++j)
        {
            std::cout << "#";
        }
        for (int j = i; j < 10; ++j)
        {
            std::cout << " ";
        }
        std::cout << "] " << (i * 10) << "%\r";
        std::cout.flush(); // Flush the output to ensure it's displayed immediately

        // Simulate a delay (e.g., processing time)
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    // Print a newline to move to the next line after the progress bar completes
    std::cout << std::endl;

    return 0;
}
