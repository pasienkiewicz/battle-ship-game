#pragma once
#include <iostream>

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
    static std::string askForInput(const std::string &question);

private:
    static void setColor(int colorCode);
};