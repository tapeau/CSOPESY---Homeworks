#include <Windows.h>
#include <iostream>
#include <chrono>
#include <ctime>

// Function to simplify setting console cursor position
void setCursorPos(int x, int y)
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (SHORT)x, (SHORT)y });
}

// Function to get current console buffer info
CONSOLE_SCREEN_BUFFER_INFO getConsoleBuffer()
{
    CONSOLE_SCREEN_BUFFER_INFO consoleBuffer;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleBuffer);
    return consoleBuffer;
}

// Function to further elaborate on the WriteConsole() function of the Windows Console API
void printConsole(std::string str, int charLimit, char alignment)
{
    DWORD printedChars;
    std::string paddedText = (alignment == 'r') ? std::string(charLimit - str.size(), ' ') + str : str + std::string(charLimit - str.size(), ' ');
    WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), paddedText.c_str(), charLimit, &printedChars, NULL);
}

// Main function
int main()
{
    // First, print date & time
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::cout << std::ctime(&now);

    // TODO: Print GPU summary table
    // GPU specifications represented as array of strongs
    std::string gpuSpecs[] = { "551.86", "551.86", "12.4", "0", "28%", "37C", "NVIDIA GeForce GTX 1080", "WDDM", "P8", "11W", "180W", "00000000:26:00.0", "On", "701MiB", "8192MiB", "0%", "N/A", "Default", "N/A" };

    // Print GPU summary table header
    std::cout << "+-----------------------------------------------------------------------------------------+\n| NVIDIA-SMI ";
    printConsole(gpuSpecs[0], 22, 'l');
    setCursorPos(36, getConsoleBuffer().dwCursorPosition.Y); std::cout << "Driver Version: "; printConsole(gpuSpecs[1], 14, 'l');
    setCursorPos(67, getConsoleBuffer().dwCursorPosition.Y); std::cout << "CUDA Version: "; printConsole(gpuSpecs[2], 7, 'l');
    std::cout << "|\n|-----------------------------------------+------------------------+----------------------+\n| GPU  Name                     TCC/WDDM  | Bus-Id          Disp.A | Volatile Uncorr. ECC |\n| Fan  Temp   Perf          Pwr:Usage/Cap |           Memory-Usage | GPU-Util  Compute M. |\n|                                         |                        |               MIG M. |\n|=========================================+========================+======================|\n| ";

    // Print GPU summary table values

    
    // TODO: Print process screen

    return 0;
}