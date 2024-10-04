#include <iostream>
#include <windows.h>
#include <string>
#include <conio.h>
#include <vector>
#include <thread>
#include <mutex>
#include <atomic>

class MarqueeConsole
{
    std::string str{"Hello world in marquee!"}, currentInput;  // String to be displayed and current user input
    int windowWidth{}, windowHeight{}, strX{}, strY{}, strXDirection{1}, strYDirection{1}; // Console dimensions, string position and movement direction
    std::vector<std::string> commandHistory;  // To store command history
    CONSOLE_SCREEN_BUFFER_INFO consoleBuffer; // Structure to store console buffer information
    std::mutex consoleMutex;  // Mutex for console access synchronization
    std::atomic<bool> running{true}; // Flag to control the loop in both threads

public:
    void start()
    {
        updateScreenSize();
        strX = (windowWidth - str.size()) / 2;
        strY = (windowHeight + 3) / 2;

        // Start the threads for keyboard polling and marquee update
        std::thread keyboardThread(&MarqueeConsole::pollKeyboard, this);
        std::thread marqueeThread(&MarqueeConsole::updateMarquee, this);

        // Wait for both threads to finish (this will never happen in the current implementation)
        keyboardThread.join();
        marqueeThread.join();
    }

private:
    // Function to check for keyboard input and process it
    void pollKeyboard()
    {
        while (running)
        {
            if (_kbhit())
            {
                char key = _getch();
                std::lock_guard<std::mutex> lock(consoleMutex); // Ensure synchronized access to shared resources
                if (key == 13)  // Enter key
                {
                    if (currentInput == "exit") // Stop the program if user types 'exit'
                    {
                        running = false;
                    }
                    else
                    {
                        commandHistory.push_back("Command processed in MARQUEE_CONSOLE: " + currentInput);
                        currentInput.clear();
                    }
                }
                else if (key == 8 && !currentInput.empty())  // Backspace key
                    currentInput.pop_back();
                else
                    currentInput.push_back(key);
            }
            Sleep(5);
        }
    }

    // Function to continuously update the marquee display
    void updateMarquee()
    {
        while (running)
        {
            {
                std::lock_guard<std::mutex> lock(consoleMutex); // Ensure synchronized access to shared resources
                system("cls");
                printHeader();
                updateScreenSize();
                moveString();
                printString();
                printInput();
                printHistory();
            }
            Sleep(5); // Sleep for a short duration to control update speed
        }
    }

    // Function to print the header of the marquee console
    void printHeader() const
    {
        std::cout << "*********************************\n";
        std::cout << "* Displaying a marquee console! *\n";
        std::cout << "*********************************\n";
    }

    // Function to update the console's screen size
    void updateScreenSize()
    {
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleBuffer);
        windowWidth = consoleBuffer.srWindow.Right - consoleBuffer.srWindow.Left + 1;
        windowHeight = consoleBuffer.srWindow.Bottom - consoleBuffer.srWindow.Top + 1;
    }

    // Function to move the string based on the current direction and boundaries
    void moveString()
    {
        strX += strXDirection;
        strY += strYDirection;
        
        // Reverse the direction if the string hits the left/right boundary
        if (strX <= 0 || strX >= (int)(windowWidth - str.size())) strXDirection *= -1;

        // Reverse the direction if the string hits the top/bottom boundary
        if (strY <= 4 || strY >= windowHeight - 7) strYDirection *= -1;
    }

    // Function to print the marquee string at its current position
    void printString() const
    {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {SHORT(strX), SHORT(strY)});
        std::cout << str;
    }

    // Function to print the input line at the bottom of the console
    void printInput() const
    {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, SHORT(windowHeight - 4)});
        std::cout << "Enter a command for MARQUEE_CONSOLE: " << currentInput;
    }

    // Function to print the command history
    void printHistory() const
    {
        for (size_t i = 0; i < commandHistory.size(); ++i)
        {
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, SHORT(windowHeight - 3 + i)});
            std::cout << commandHistory[commandHistory.size() - 1 - i] << "\n";
        }
    }
};

// Main function
int main()
{
    // Create an instance of MarqueeConsole and start it
    MarqueeConsole console;
    console.start();
    return 0;
}
