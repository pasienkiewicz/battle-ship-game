#include "Computer.h"

Computer::Computer()
	:
	state(0),
	step(0)
{
	name = "Computer";
	shipSize[0] = 5;
	shipSize[1] = 4;
	shipSize[2] = 3;
	shipSize[3] = 3;
	shipSize[4] = 2;
	automaticShipSpawn();
}

bool Computer::attack(Ships& gamer)
{
	if (state == 0)
	{
		while (true)
		{
			y = rand() % getcolumns();
			x = rand() % getrows();

			if (checkShotGrid(y, x))
			{
				if (checkIfShip(y, x, gamer))
				{
					shotgrid[y][x] = '$';
					gamer.setChar(y, x);
					state++;
					x2 = x;
					y2 = y;
					return true;
					//Sentence over here
				}
				else
				{
					shotgrid[y][x] = 'X';
					//sentence over here
					return false;
				}
			}
		}
	}
	else if (state == 1)
	{
		if (x2 + 1 == getrows()&&step==0)
		{
			state++;
			x2 = x;
			return attack(gamer);
		}
		else if (x2 + 1 == getrows() && step > 0)
		{
			state += 2;
			x2 = x;
			return attack(gamer);
		}
		else
		{
			if (checkIfShip(y2, x2 + 1, gamer))
			{
				shotgrid[y2][x2 + 1] = '$';
				gamer.setChar(y, x2 + 1);
				x2 += 1;
				step++;
				return true;
			}
			else
			{
				shotgrid[y2][x2 + 1] = 'X';
				state++;
				x2 = x;
				return false;
			}
		}
	}
	else if (state == 2)
	{
		if (y2 + 1 == getcolumns() && step == 0)
		{
			state++;
			y2 = y;
			return attack(gamer);
		}
		else if (y2 + 1 == getcolumns() && step > 0)
		{
			state += 2;
			y2 = y;
			return attack(gamer);
		}
		else
		{
			if (checkIfShip(y2 + 1, x2, gamer))
			{
				shotgrid[y2 + 1][x2] = '$';
				gamer.setChar(y2 + 1, x2);
				y2 += 1;
				step++;
				return true;
			}
			else
			{
				shotgrid[y2][x2 + 1] = 'X';
				state++;
				y2 = y;
				return false;
			}
		}
	}
	else if (state == 3)
	{
		if (x2 - 1 == -1 && step == 0)
		{
			state++;
			x2 = x;
			return attack(gamer);
		}
		else
		{
			if (checkIfShip(y2, x2 - 1, gamer))
			{
				shotgrid[y2][x2 - 1] = '$';
				gamer.setChar(y, x2 - 1);
				x2 -= 1;
				return true;
			}
			else
			{
				shotgrid[y2][x2 - 1] = 'X';
				state++;
				x2 = x;
				return false;
			}
		}
	}
	else if (state == 4)
	{
		if (y2 - 1 == -1)
		{
			state = 0;
			return attack(gamer);
		}
		else
		{
			if (checkIfShip(y2 - 1, x2, gamer))
			{
				shotgrid[y2 - 1][x2] = '$';
				gamer.setChar(y2 - 1, x2);
				y2 -= 1;
				return true;
			}
			else
			{
				shotgrid[y2][x2 + 1] = 'X';
				state=0;
				y2 = y;
				return false;
			}
		}
	}
}
	
bool Computer::inicialRecursion(Ships& gamer)
{
	if (!(shotgrid[y][x + 1] == 'X'))
	{
		if (checkIfShip(y, x, gamer))
		{
		}
	}
	return false;
}
