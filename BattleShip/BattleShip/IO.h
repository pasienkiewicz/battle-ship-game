#pragma once
#include <iostream>

using std::cin;
using std::cout;
using std::string;

class IO
{
public:
    static constexpr int WHITE = 0;
    static constexpr int GREEN = 32;
    static constexpr int CYAN = 36;
    static constexpr int YELLOW = 33;
    static constexpr int RED = 31;

public:
    static void resetColor();
    static void setGreen();
    static void setCyan();
    static void setYellow();
    static void setRed();
    static void clearScreen();
    static string askForInput(const string &question);

private:
    static void setColor(int colorCode);
};