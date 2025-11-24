#include "IO.h"

void IO::resetColor()
{
    setColor(IO::WHITE);
}

void IO::setGreen()
{
    setColor(IO::GREEN);
}

void IO::setCyan()
{
    setColor(IO::CYAN);
}

void IO::setYellow()
{
    setColor(IO::YELLOW);
}

void IO::setRed()
{
    setColor(IO::RED);
}

void IO::clearScreen()
{
    std::cout << "\033[2J\033[1;1H";
}

void IO::setColor(int colorCode)
{
    std::cout << "\033[" << colorCode << "m";
}

std::string IO::askForInput(const std::string &question)
{
    std::string answer;
    std::cout << question;
    std::cin >> answer;

    return answer;
}