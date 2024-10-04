#include <iostream>
#include <windows.h>
#include <string>
#include <conio.h>
#include <vector>

// Encapsulate marquee console functionalities as one class
class MarqueeConsole
{
    std::string str{"Hello world in marquee!"}, currentInput;  // String to be displayed and current user input
    int windowWidth{}, windowHeight{}, strX{}, strY{}, strXDirection{1}, strYDirection{1}; // Console dimensions, string position and movement direction
    std::vector<std::string> commandHistory;  // To store command history
    CONSOLE_SCREEN_BUFFER_INFO consoleBuffer; // Structure to store console buffer information

public:
    // Function to start the marquee and handle the main loop
    void start()
    {
        updateScreenSize();
        strX = (windowWidth - str.size()) / 2;
        strY = (windowHeight + 3) / 2;
        
        // Infinite loop to update the marquee display
        while (true)
        {
            pollKeyboard();
            updateMarquee();
            Sleep(4);
        }
    }

private:
    // Function to check for keyboard input and process it
    void pollKeyboard()
    {
        if (_kbhit())
        {
            char key = _getch();
            if (key == 13)
            {
                commandHistory.push_back("Command processed in MARQUEE_CONSOLE: " + currentInput);
                currentInput.clear();
            }
            else if (key == 8 && !currentInput.empty()) currentInput.pop_back();
            else currentInput.push_back(key);
        }
    }

    // Function to update the marquee display
    void updateMarquee()
    {
        system("cls");
        printHeader();
        updateScreenSize();
        moveString();
        printString();
        printInput();
        printHistory();
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
    MarqueeConsole().start();
    return 0;
}
