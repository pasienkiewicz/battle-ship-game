#pragma once
#include <cctype>
#include <stdexcept>

struct Coordinates
{
    static const int maxX = 10;
    static const int maxY = 10;
    const int x;
    const int y;

    Coordinates(const std::string &coordinates)
        : x(transformCharToInt(coordinates.at(0))),
          y(transformCharToInt(coordinates.at(1)))
    {
        if (2 != coordinates.size())
        {
            throw std::invalid_argument("Coordinates string must have 2 characters");
        }
    }

    Coordinates(int x, int y)
        : x(x), y(y)
    {
        if (!areValid(x, y))
        {
            throw std::out_of_range("Coordinates are out of valid range");
        }
    }

public:
    static bool areValid(int x, int y)
    {
        return x >= 0 &&
               y >= 0 &&
               x < maxX &&
               y < maxY;
    }

private:
    int transformCharToInt(char character)
    {
        character = std::tolower(character);

        if (std::isdigit(character))
        {
            return character - '0';
        }

        if (character >= 'a' && character <= 'j')
        {
            return character - 'a';
        }

        throw std::invalid_argument("Invalid coordinate character");
    }
};
