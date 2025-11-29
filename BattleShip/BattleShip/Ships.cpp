#include "Ships.h"

Ships::Ships()
{
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

char Ships::getAttackedChar(Coordinates coordinates)
{
	return shipgrid[0][coordinates.y][coordinates.x];
}

void Ships::setHitChar(Coordinates coordinates)
{
	shipgrid[0][coordinates.y][coordinates.x] = '$';
	shipgrid[1][coordinates.y][coordinates.x] = ' ';
}

void Ships::setMissChar(Coordinates coordinates)
{
	shipgrid[0][coordinates.y][coordinates.x] = 'X';
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
	auto it = newset.find(' ');
	newset.erase(it);
	if (newset.size() < static_cast<std::set<char>::size_type>(numberOfShips))
	{
		numberOfShips = newset.size();
		numberOfShipTypes.clear();
		for (auto elem : newset)
		{
			numberOfShipTypes.push_back(elem);
		}
		return true;
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
	for (int i = 0; i < numberOfShips; i++)
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
			if (isShipPlacedInCorrectPossition(Coordinates(x, y), direction, shipSize[i] - 1))
			{
				setShip(Coordinates(x, y), direction, shipSize[i] - 1, shipType[i]);
				break;
			}
		}
	}
}

bool Ships::isShotAttemptValid(Coordinates coordinates)
{
	return !(shotgrid[coordinates.y][coordinates.x] == 'X') &&
		   !(shotgrid[coordinates.y][coordinates.x] == '$');
}

void Ships::setShip(Coordinates coordinates, bool direction, int shipSize, char shipType)
{
	int goesRight = 0, goesDown = 0;
	if (direction == 1)
		goesRight = shipSize;
	else
		goesDown = shipSize;

	for (int i = coordinates.y; i <= coordinates.y + goesDown; i++)
	{
		for (int j = coordinates.x; j <= coordinates.x + goesRight; j++)
		{
			if (advancedShipSpawn)
			{
				if (coordinates.y - 1 != -1)
					spawngrid[i - 1][j] = 'O';
				if (coordinates.x - 1 != -1)
					spawngrid[i][j - 1] = 'O';
				if (coordinates.y + 1 != 10)
					spawngrid[i + 1][j] = 'O';
				if (coordinates.x + 1 != 10)
					spawngrid[i][j + 1] = 'O';
			}
			shipgrid[0][i][j] = 'O';
			shipgrid[1][i][j] = shipType;
			shipgrid[2][i][j] = shipType;
		}
	}
}

bool Ships::didHitShip(Coordinates coordinates, Ships &oponentShip)
{
	return 'O' == oponentShip.getAttackedChar(coordinates);
}

bool Ships::isShipPlacedInCorrectPossition(Coordinates coordinates, bool direction, int shipSize)
{
	int goesRight = 0, goesDown = 0;
	if (direction == 1)
		goesRight = shipSize;
	else
		goesDown = shipSize;

	for (int i = coordinates.y; i <= coordinates.y + goesDown; i++)
	{
		for (int j = coordinates.x; j <= coordinates.x + goesRight; j++)
		{
			if (advancedShipSpawn)
			{
				if (spawngrid[i][j] == 'O')
					return false;
			}
			else if (shipgrid[0][i][j] == 'O')
				return false;
		}
	}

	return true;
}
