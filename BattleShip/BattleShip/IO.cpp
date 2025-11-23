#include "IO.h"

void IO::resetColor() {
    setColor(IO::WHITE);
}

void IO::setRed() {
    setColor(IO::RED);
}

void IO::setYellow() {
    setColor(IO::YELLOW);
}

void IO::setGreen() {
    setColor(IO::GREEN);
}

void IO::clearScreen() {
    std::cout << "\033[2J\033[1;1H";
}

void IO::setColor(int colorCode) {
    std::cout << "\033[" << colorCode << "m";
}