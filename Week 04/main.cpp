#include <Windows.h>
#include <iostream>
#include <chrono>
#include <ctime>

// Main function
int main()
{
    // First, print date & time
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::cout << std::ctime(&now);

    // TODO: Print GPU summary screen
    
    // TODO: Print process screen

    return 0;
}