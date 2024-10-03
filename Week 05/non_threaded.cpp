#include <iostream>
#include <windows.h>
#include <string>
#include <conio.h>
#include <vector>

// Encapsulate marquee console functionalities as one class
class MarqueeConsole
{
    std::string str{"Hello world in marquee!"}, currentInput;
    int windowWidth{}, windowHeight{}, strX{}, strY{}, strXDirection{1}, strYDirection{1};
    std::vector<std::string> commandHistory;
    CONSOLE_SCREEN_BUFFER_INFO consoleBuffer;

public:
    void start()
    {
        // TODO
    }

private:
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

    void printHeader() const
    {
        std::cout << "*********************************\n* Displaying a marquee console! *\n*********************************\n";
    }

    // TODO: Implement member functions for string display and user input handling

};

// Main function
int main()
{
    // TODO
    return 0;
}
