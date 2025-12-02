#pragma once

using std::invalid_argument;
using std::isdigit;
using std::string;
using std::tolower;

struct Coordinates
{
public:
    static const int maxX = 10;
    static const int maxY = 10;

private:
    int xx;
    int yy;

public:
    Coordinates(const string &coordinates)
        : xx(transformCharToInt(coordinates.at(0))),
          yy(transformCharToInt(coordinates.at(1)))
    {
        if (2 != coordinates.size())
        {
            throw invalid_argument("Coordinates string must have 2 characters");
        }
    }

    Coordinates(int x, int y)
        : xx(x), yy(y)
    {
        if (!areValid(x, y))
        {
            throw out_of_range("Coordinates are out of valid range");
        }
    }

    int x() const { return xx; }
    int y() const { return yy; }

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
        character = tolower(character);

        if (isdigit(character))
        {
            return character - '0';
        }

        if (character >= 'a' && character <= 'j')
        {
            return character - 'a';
        }

        throw invalid_argument("Invalid coordinate character");
    }
};
