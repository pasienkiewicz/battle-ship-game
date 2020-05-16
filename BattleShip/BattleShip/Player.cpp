#include "Player.h"

Player::Player()
{
    shipsType[0] = "Carier (space 5): ";
    shipsType[1] = "Battleship (space 4): ";
    shipsType[2] = "Destroyer (space 3): ";
    shipsType[3] = "Submarine (space 3): ";
    shipsType[4] = "Patrol Boat (space 2): ";
    spawnShip();
}

void Player::spawnShip()
{		
    string a, b;
    for (int i = 0; i < numberOfShips; i++)
    {
        while (true)
        {
            Board::drawSigleBoard();
            cout << "Enter ship start and end koordinate. Ex. Submarine (size 3): 1A 1C " << endl << endl;
            cout << shipsType[i];
            cin >> a >> b;
            cin.ignore();
            convertCoordinates(a, b);
            if (checkDoubleCoordinates())
            {
                bool direction=checkDirection();
                if (checkOverlap(y, x, direction, shipSize[i]))
                {
                    if (checkSize(shipSize[i]))
                    {
                        setShip(y, x, direction, shipSize[i]-1, shipType[i]);
                        break;
                    }
                    else
                    {
                        cout << "Unappropriated ship size! Please enter other coordinates" << endl;
                        cout << "Press \"enter\" key to input new koordinates...";
                        cin.get();
                    }
                }
                else
                {
                    cout << "There is already ship in those coordinates! Please enter other coordinates" << endl;
                    cout << "Press \"enter\" key to input new koordinates...";
                    cin.get();
                }
            }
            else
            {
                cout << "Wrong coordinates! Please enter other coordinates.";
                cout << "Press \"enter\" key to input new koordinates...";
                cin.get();
            }
        }
        Board::drawSigleBoard();
    }        
}

bool Player::attack(Ships& oponentShip)
{
    string a;
    drawTwoBoards();
    while (true)
    {
        cout << "Shot koordinate. Ex. 1A: ";
        cin >> a;
        cin.ignore();
        convertCoordinates(a);

        if (checkCoordinates())
        {
            if (checkShotGrid(y,x))
            {
                if (checkIfShip(y, x, oponentShip))
                {
                    shotgrid[y][x] = '$';
                    oponentShip.setChar(y, x);
                    return true;
                }
                else
                {
                    shotgrid[y][x] = 'X';
                    return false;
                }
            }
            else
            {
                cout << "U have laready shoot there! Please enter other coordinates.";
                cout << "Press \"enter\" key to input new koordinates...";
                cin.get();
            }
        }
        else
        {
            cout << "Wrong coordinates! Please enter other coordinates.";
            cout << "Press \"enter\" key to input new koordinates...";
            cin.get();
        }

    }
}

void Player::convertCoordinates(string a, string b)
{
    y = encript(a.at(0));
    x = encript(a.at(1));
    y2 = encript(b.at(0));
    x2 = encript(b.at(1));
}

void Player::convertCoordinates(string a)
{
    y = encript(a.at(0));
    x = encript(a.at(1));
}

bool Player::checkDoubleCoordinates()
{
    if ((y == -1 || x == -1 || y2 == -1 || x2 == -1) || (y + x >= y2 + x2))
    {
        return false;
    }
    return true;
}

bool Player::checkCoordinates()
{
    if ( y == -1 || x == -1 )
    {
        return false;
    }
    return true;
}

bool Player::checkSize(int shipSize)
{
    if ((x2 - x + y2 - y + 1) == shipSize)
        return true;
    else
        return false;
}

bool Player::checkDirection()
{
    if (x == x2)
        return 0;
    if (y == y2)
        return 1;
}

int Player::encript(char a)
{
    if (isdigit(a))
        return a-'0';
    if (a == 'a' || a== 'A')
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
