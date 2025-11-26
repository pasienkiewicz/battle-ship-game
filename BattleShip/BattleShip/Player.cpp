#include "Player.h"
Player::Player()
{
    this->name = "Player";

    shipsType[0] = "Carier (space 5): ";
    shipsType[1] = "Battleship (space 4): ";
    shipsType[2] = "Destroyer (space 3): ";
    shipsType[3] = "Submarine (space 3): ";
    shipsType[4] = "Patrol Boat (space 2): ";
}

void Player::spawnShip()
{
    string firstCoordinateInput, secondCoordinateInput;
    for (int i = 0; i < numberOfShips; i++)
    {
        while (true)
        {
            Board::drawSigleBoard();
            cout << "Enter ship start and end koordinate. Ex. Submarine (size 3): A1 C1 " << endl
                 << endl;
            cout << shipsType[i];
            cin >> firstCoordinateInput >> secondCoordinateInput;
            cin.ignore();
            std::optional<Coordinates> firstCoordinates;
            std::optional<Coordinates> secondCoordinates;
            try
            {
                firstCoordinates.emplace(Coordinates(firstCoordinateInput));
                secondCoordinates.emplace(Coordinates(secondCoordinateInput));
            }
            catch (const std::invalid_argument &e)
            {
                cout << "Wrong coordinates! Please enter other coordinates.";
                cout << "Press \"enter\" key to input new koordinates...";
                cin.get();

                continue;
            }

            bool shipDirection = getShipDirection(*firstCoordinates, *secondCoordinates);
            if (!isShipPlacedInCorrectPossition(*firstCoordinates, shipDirection, shipSize[i]))
            {
                cout << "There is already ship in those coordinates! Please enter other coordinates" << endl;
                cout << "Press \"enter\" key to input new koordinates...";
                cin.get();

                continue;
            }
            if (!isShipCorrectSize(*firstCoordinates, *secondCoordinates, shipSize[i]))
            {
                cout << "Unappropriated ship size! Please enter other coordinates" << endl;
                cout << "Press \"enter\" key to input new koordinates...";
                cin.get();
                continue;
            }

            setShip(*firstCoordinates, shipDirection, shipSize[i] - 1, shipType[i]);

            break;
        }
    }
}

bool Player::attack(Ships &computer)
{
    string coordinatesInput;
    drawTwoBoards(computer);
    while (true)
    {
        cout << "Shot koordinate. Ex. A1: ";
        cin >> coordinatesInput;
        cin.ignore();
        std::optional<Coordinates> coordinates;

        try
        {
            coordinates.emplace(Coordinates(coordinatesInput));
        }
        catch (const std::invalid_argument &e)
        {
            cout << "Wrong coordinates! Please enter other coordinates.";
            cout << "Press \"enter\" key to input new koordinates...";
            cin.get();

            continue;
        }

        if (!isShotAttemptValid(*coordinates))
        {
            cout << "Wrong coordinates! Please enter other coordinates.";
            cout << "Press \"enter\" key to input new koordinates...";
            cin.get();

            continue;
        }

        Coordinates coord = *coordinates;

        if (!didHitShip(coord, computer))
        {
            displayInfo(name + ": miss");
            shotgrid[coord.y][coord.x] = 'X';

            return false;
        }

        shotgrid[coord.y][coord.x] = '$';
        computer.setHitChar(coord);
        if (computer.checkIfSink())
            displayInfo(name + ": oponent ship sink");
        else
            displayInfo(name + ": oponent ship hit");

        return true;
    }
}

bool Player::isShipCorrectSize(Coordinates firstCoordinates, Coordinates secondCoordinates, int shipSize)
{
    return secondCoordinates.x - firstCoordinates.x + secondCoordinates.y - firstCoordinates.y == shipSize;
}

bool Player::getShipDirection(Coordinates firstCoordinates, Coordinates secondCoordinates)
{
    if (firstCoordinates.x == secondCoordinates.x)
        return false;
    if (firstCoordinates.y == secondCoordinates.y)
        return true;

    throw invalid_argument("Invalid shipDirection");
}
