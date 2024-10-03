#include <Windows.h>
#include <iostream>
#include <chrono>
#include <ctime>

// Function prototypes
void setCursorPos(int x, int y);
int getCursorPosY();
void printProcess(std::string str, int charLimit, char alignment);
void printConsole(std::string str, int charLimit, char alignment);

// Main function
int main()
{
    // First, print date & time
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::cout << std::ctime(&now);

    // GPU specifications represented as array of strings
    std::string gpuSpecs[] = { "551.86", "551.86", "12.4", "0", "28%", "37C", "NVIDIA GeForce GTX 1080", "WDDM", "P8", "11W", "180W", "00000000:26:00.0", "On", "701MiB", "8192MiB", "0%", "N/A", "Default", "N/A" };

    // Print GPU summary table header
    std::cout << "+-----------------------------------------------------------------------------------------+\n| NVIDIA-SMI ";
    printConsole(gpuSpecs[0], 22, 'l');
    setCursorPos(36, getCursorPosY()); std::cout << "Driver Version: "; printConsole(gpuSpecs[1], 14, 'l');
    setCursorPos(67, getCursorPosY()); std::cout << "CUDA Version: "; printConsole(gpuSpecs[2], 7, 'l'); std::cout << "  ";
    std::cout << "|\n|-----------------------------------------+------------------------+----------------------+\n| GPU  Name                     TCC/WDDM  | Bus-Id          Disp.A | Volatile Uncorr. ECC |\n| Fan  Temp   Perf          Pwr:Usage/Cap |           Memory-Usage | GPU-Util  Compute M. |\n|                                         |                        |               MIG M. |\n|=========================================+========================+======================|\n| ";

    // Print GPU summary table values
    printConsole(gpuSpecs[3], 3, 'r'); setCursorPos(7, getCursorPosY());
    printConsole(gpuSpecs[6], 23, 'l'); setCursorPos(31, getCursorPosY());
    printConsole(gpuSpecs[7], 9, 'r'); std::cout << "  | "; printConsole(gpuSpecs[11], 18, 'r'); std::cout << " ";
    printConsole(gpuSpecs[12], 3, 'r'); std::cout << " | "; printConsole(gpuSpecs[16], 20, 'r'); std::cout << " |\n| ";
    printConsole(gpuSpecs[4], 4, 'l'); std::cout << " "; printConsole(gpuSpecs[5], 4, 'r');
    setCursorPos(15, getCursorPosY()); printConsole(gpuSpecs[8], 2, 'r'); setCursorPos(28, getCursorPosY());
    printConsole(gpuSpecs[9], 5, 'r'); std::cout << " / "; printConsole(gpuSpecs[10], 5, 'r'); std::cout << " |  ";
    printConsole(gpuSpecs[13], 9, 'r'); std::cout << " / "; printConsole(gpuSpecs[14], 9, 'r'); std::cout << " |";
    setCursorPos(72, getCursorPosY()); printConsole(gpuSpecs[15], 4, 'r');
    setCursorPos(79, getCursorPosY()); printConsole(gpuSpecs[17], 10, 'r');
    std::cout << " |\n|";
    setCursorPos(42, getCursorPosY()); std::cout << "|"; setCursorPos(67, getCursorPosY()); std::cout << "| "; printConsole(gpuSpecs[16], 20, 'r'); std::cout << " |\n+-----------------------------------------+------------------------+----------------------+\n";
    
    // Print process table
    // Process list represented as 2-D array
    std::string processes[5][7] = {
        {"0", "N/A", "N/A", "2628", "C+G", "C:\\Program Files\\Google\\Chrome\\Application\\chrome.exe", "N/A"},
        {"0", "N/A", "N/A", "3860", "C+G", "C:\\Users\\Admin\\AppData\\Roaming\\Spotify\\Spotify.exe", "N/A"},
        {"0", "N/A", "N/A", "6592", "C+G", "C:\\Program Files (x86)\\Steam\\steamapps\\common\\Counter-Strike Global Offensive\\game\\bin\\win64\\cs2.exe", "40%"},
        {"0", "N/A", "N/A", "9952", "C+G", "C:\\Programs Files\\Wireshark\\Wireshark.exe", "N/A"},
        {"0", "N/A", "N/A", "15412", "C+G", "C:\\Program Files (x86)\\The Sims 4\\Game\\Bin\\TS4_x64.exe", "25%"}
    };
    std::cout << "\n+-----------------------------------------------------------------------------------------+\n| Processes:                                                                              |\n|  GPU   GI   CI        PID   Type   Process name                              GPU Memory |\n|        ID   ID                                                               Usage      |\n|=========================================================================================|\n";
    for (int i = 0; i < 5; i++) {
        std::cout << "|";
        setCursorPos(3, getCursorPosY()); printConsole(processes[i][0], 3, 'r');
        setCursorPos(9, getCursorPosY()); printConsole(processes[i][1], 3, 'l');
        setCursorPos(14, getCursorPosY()); printConsole(processes[i][2], 3, 'l');
        setCursorPos(18, getCursorPosY()); printConsole(processes[i][3], 9, 'r');
        setCursorPos(28, getCursorPosY()); printConsole(processes[i][4], 6, 'r');
        setCursorPos(37, getCursorPosY()); printProcess(processes[i][5], 38, 'l');
        setCursorPos(81, getCursorPosY()); printConsole(processes[i][6], 3, 'r');
        setCursorPos(90, getCursorPosY()); std::cout << "|\n";
    }
    std::cout << "+-----------------------------------------------------------------------------------------+\n";

    return 0;
}

// Function to simplify setting console cursor position
void setCursorPos(int x, int y)
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (SHORT)x, (SHORT)y });
}

// Function to get the current Y-axis position of console cursor
int getCursorPosY()
{
    CONSOLE_SCREEN_BUFFER_INFO consoleBuffer;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleBuffer);
    return consoleBuffer.dwCursorPosition.Y;
}

// Function to print a process name inside the process table (according to nvidia-smi format)
void printProcess(std::string str, int charLimit, char alignment)
{
    if ((int)str.size() > charLimit) str = "..." + str.substr(str.size() - charLimit + 3);
    printConsole(str, charLimit, alignment);
}

// Function to further elaborate on the WriteConsole() function of the Windows Console API
void printConsole(std::string str, int charLimit, char alignment)
{
    DWORD printedChars;
    std::string paddedText = (alignment == 'r') ? std::string(charLimit - str.size(), ' ') + str : str + std::string(charLimit - str.size(), ' ');
    WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), paddedText.c_str(), charLimit, &printedChars, NULL);
}
