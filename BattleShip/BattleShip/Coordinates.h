#pragma once
#include <cctype>
#include <stdexcept>

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

struct Coordinates
{
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
};
