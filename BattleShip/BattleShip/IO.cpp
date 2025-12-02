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
    cout << "\033[2J\033[1;1H";
}

void IO::setColor(int colorCode)
{
    cout << "\033[" << colorCode << "m";
}

string IO::askForInput(const string &question)
{
    string answer;
    cout << question;
    cin >> answer;

    return answer;
}