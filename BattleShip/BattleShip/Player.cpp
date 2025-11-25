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
    string a, b;
    for (int i = 0; i < numberOfShips; i++)
    {
        while (true)
        {
            Board::drawSigleBoard();
            cout << "Enter ship start and end koordinate. Ex. Submarine (size 3): 1A 1C " << endl
                 << endl;
            cout << shipsType[i];
            cin >> a >> b;
            cin.ignore();
            convertCoordinates(a, b);

            if (!areDoubleCoordinatesValid())
            {
                cout << "Wrong coordinates! Please enter other coordinates.";
                cout << "Press \"enter\" key to input new koordinates...";
                cin.get();

                continue;
            }
            bool shipDirection = getShipDirection();
            if (!isShipPlacedInCorrectPossition(y, x, shipDirection, shipSize[i]))
            {
                cout << "There is already ship in those coordinates! Please enter other coordinates" << endl;
                cout << "Press \"enter\" key to input new koordinates...";
                cin.get();

                continue;
            }
            if (!isShipCorrectSize(shipSize[i]))
            {
                cout << "Unappropriated ship size! Please enter other coordinates" << endl;
                cout << "Press \"enter\" key to input new koordinates...";
                cin.get();
                continue;
            }

            setShip(y, x, shipDirection, shipSize[i] - 1, shipType[i]);

            break;
        }
    }
}

bool Player::attack(Ships &computer)
{
    string a;
    drawTwoBoards(computer);
    while (true)
    {
        cout << "Shot koordinate. Ex. 1A: ";
        cin >> a;
        cin.ignore();
        convertCoordinates(a);

        if (!areCoordinatesValid())
        {
            cout << "Wrong coordinates! Please enter other coordinates.";
            cout << "Press \"enter\" key to input new koordinates...";
            cin.get();

            continue;
        }

        if (!isHitAttemptValid(y, x))
        {
            cout << "Wrong coordinates! Please enter other coordinates.";
            cout << "Press \"enter\" key to input new koordinates...";
            cin.get();

            continue;
        }

        if (!didHitShip(y, x, computer))
        {
            displayInfo(name + ": miss");
            shotgrid[y][x] = 'X';

            return false;
        }

        shotgrid[y][x] = '$';
        computer.setHitChar(y, x);
        if (computer.checkIfSink())
            displayInfo(name + ": oponent ship sink");
        else
            displayInfo(name + ": oponent ship hit");

        return true;
    }
}

void Player::convertCoordinates(string a, string b)
{
    y = transformCharToInt(a.at(0));
    x = transformCharToInt(a.at(1));
    y2 = transformCharToInt(b.at(0));
    x2 = transformCharToInt(b.at(1));
}

void Player::convertCoordinates(string a)
{
    y = transformCharToInt(a.at(0));
    x = transformCharToInt(a.at(1));
}

bool Player::areDoubleCoordinatesValid()
{
    if ((y == -1 || x == -1 || y2 == -1 || x2 == -1) || (y + x >= y2 + x2))
    {
        return false;
    }
    return true;
}

bool Player::areCoordinatesValid()
{
    if (y == -1 || x == -1)
    {
        return false;
    }
    return true;
}

bool Player::isShipCorrectSize(int shipSize)
{
    if ((x2 - x + y2 - y + 1) == shipSize)
        return true;
    else
        return false;
}

bool Player::getShipDirection()
{
    if (x == x2)
        return false;
    if (y == y2)
        return true;

    throw invalid_argument("Invalid shipDirection");
}

int Player::transformCharToInt(char a)
{
    if (isdigit(a))
        return a - '0';
    if (a == 'a' || a == 'A')
        return 0;
    else if (a == 'b' || a == 'B')
        return 1;
    else if (a == 'c' || a == 'C')
        return 2;
    else if (a == 'd' || a == 'D')
        return 3;
    else if (a == 'e' || a == 'E')
        return 4;
    else if (a == 'f' || a == 'F')
        return 5;
    else if (a == 'g' || a == 'G')
        return 6;
    else if (a == 'h' || a == 'H')
        return 7;
    else if (a == 'i' || a == 'I')
        return 8;
    else if (a == 'j' || a == 'J')
        return 9;
    else
        return -1;
}
