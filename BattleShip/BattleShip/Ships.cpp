#include "Ships.h"

Ships::Ships()
{
	numberOfShips = TotalnumberOfShips;
	shipSize[0] = 5;
	shipSize[1] = 4;
	shipSize[2] = 3;
	shipSize[3] = 3;
	shipSize[4] = 2;

	shipType[0] = '0';
	shipType[1] = '1';
	shipType[2] = '2';
	shipType[3] = '3';
	shipType[4] = '4';
}

char Ships::getAttackedChar(int y, int x)
{
	return shipgrid[0][y][x];
}

void Ships::setChar(int y, int x)
{
	shipgrid[0][y][x] = '$';
	shipgrid[1][y][x] = ' ';
}

bool Ships::checkIfSink()
{
	set<char> newset;
	for (int i = 0; i < getcolumns(); i++)
	{
		for (int j = 0; j < getrows(); j++)
		{
			newset.insert(shipgrid[1][i][j]);
		}
	}
	if (newset.size() <= numberOfShips)
	{
		return true;
		numberOfShips = newset.size();
	}
	else
		return false;
}

bool Ships::checkLost()
{
	for (int i = 0; i < getcolumns(); i++)
		for (int j = 0; j < getrows(); j++)
			if (shipgrid[0][i][j] == 'O')
				return 0;
	return 1;
}

void Ships::automaticShipSpawn()
{
	bool direction = 0;
	int x, y;
	for (int i = 0; i < TotalnumberOfShips; i++)
	{
		while (true)
		{
			y = rand() % getcolumns();
			x = rand() % getrows();
			if (y > getcolumns() - shipSize[i])
			{
				x = rand() % (getrows() - shipSize[i]);
				direction = 1;
			}
			else if (y <= getcolumns() - shipSize[i])
			{
				if (x > 5)
					direction = 0;
				else
					direction = rand() % 2;
			}
			if (checkOverlap(y, x, direction, shipSize[i] - 1))
			{
				setShip(y, x, direction, shipSize[i] - 1, shipType[i]);
				break;
			}
		}
	}
}

bool Ships::checkShotGrid(int y, int x)
{
	return !(shotgrid[y][x] == 'X') && !(shotgrid[y][x] == '$');
}

void Ships::setShip(int y, int x, bool direction, int shipSize, char shipType)
{
	int goesRight = 0, goesDown = 0;
	if (direction == 1) 
		goesRight = shipSize;
	else 
		goesDown = shipSize;

	for (int i = y; i <= y + goesDown; i++)
	{
		for (int j = x; j <= x + goesRight; j++)
		{
			shipgrid[0][i][j] = 'O';
			shipgrid[1][i][j] = shipType;
		}
	}
}

bool Ships::checkIfShip(int y, int x, Ships& oponentShip)
{
	if (oponentShip.getAttackedChar(y, x) == 'O')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

bool Ships::checkOverlap(int y, int x, bool direction, int shipSize)
{
	int goesRight = 0, goesDown = 0;
	if (direction == 1)
		goesRight = shipSize;
	else
		goesDown = shipSize;

	for (int i = y; i <= y + goesDown; i++)
	{
		for (int j = x; j <= x + goesRight; j++)
		{
			if (shipgrid[0][i][j] == 'O')
				return 0;
		}
	}
	return 1;
}


