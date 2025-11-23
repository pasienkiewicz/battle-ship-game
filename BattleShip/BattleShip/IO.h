#pragma once
#include <iostream>

class IO {
    static constexpr int WHITE = 0;
    static constexpr int RED = 31;
    static constexpr int GREEN = 32;
    static constexpr int YELLOW = 33;
public:
    static void resetColor();
    static void setRed();
    static void setYellow();
    static void setGreen();
    static void clearScreen();
private:
    static void setColor(int colorCode);
};