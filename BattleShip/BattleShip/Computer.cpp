#include "Computer.h"

Computer::Computer()
	:
	attackStage(0)
{
	shipSize[0] = 5;
	shipSize[1] = 4;
	shipSize[2] = 3;
	shipSize[3] = 3;
	shipSize[4] = 2;
}

bool Computer::attack(Ships& gamer)
{
	if (attackStage == 0)
	{
		while (true)
		{
			if (advancedAtack) {
				y = rand() % getcolumns();
				x = rand() % getrows();
				if ((y+x) % 2 != 0)
					continue;
			}
			else {
				y = rand() % getcolumns();
				x = rand() % getrows();
			}

			if (checkShotGrid(y, x))
			{
				if (checkIfShip(y, x, gamer))
				{
					shotgrid[y][x] = '$';
					gamer.setHitChar(y, x);
					if (gamer.checkIfSink()) {
						gamer.displayInfo("Computer " + name + ": oponent ship sink");
						attackStage = 0;
						continueAttack = false;
						return true;
					}
					gamer.displayInfo("Computer " + name + ": oponent ship hit");
					attackStage++;
					x2 = x;
					y2 = y;
					return true;
					//Sentence over here
				}
				else
				{
					gamer.setMissChar(y, x);
					shotgrid[y][x] = 'X';
					gamer.displayInfo("Computer " + name + ": miss");
					//sentence over here
					return false;
				}
			}
		}
	}
	else if (attackStage == 1)
	{
		if (x2 + 1 == getrows()&&!continueAttack)
		{
			attackStage++;
			x2 = x;
			return attack(gamer);
		}
		else if (x2 + 1 == getrows() && continueAttack)
		{
			attackStage += 2;
			x2 = x;
			return attack(gamer);
		}
		else
		{
			if (!checkShotGrid(y2, x2 + 1)) {
				if (continueAttack) {
					attackStage += 2;
				}
				else
					attackStage++;
				x2 = x;
				return attack(gamer);
			}
			else if (checkIfShip(y2, x2 + 1, gamer))
			{
				shotgrid[y2][x2 + 1] = '$';
				gamer.setHitChar(y2, x2 + 1);
				if (gamer.checkIfSink()) {
					gamer.displayInfo("Computer " + name + ": oponent ship sink");
					attackStage = 0;
					continueAttack = false;
					return true;
				}
				gamer.displayInfo("Computer " + name + ": oponent ship hit");
				x2 += 1;
				continueAttack = true;
				return true;
			}
			else
			{
				shotgrid[y2][x2 + 1] = 'X';
				gamer.setMissChar(y2, x2 + 1);
				gamer.displayInfo("Computer " + name + ": miss");
				if (continueAttack) {
					attackStage += 2;
				} else
					attackStage++;
				x2 = x;
				return false;
			}
		}
	}
	else if (attackStage == 2)
	{
		if (y2 + 1 == getcolumns() &&!continueAttack)
		{
			attackStage++;
			y2 = y;
			return attack(gamer);
		}
		else if (y2 + 1 == getcolumns() && continueAttack)
		{
			attackStage += 2;
			y2 = y;
			return attack(gamer);
		}
		else
		{
			if (!checkShotGrid(y2 + 1, x2)) {
				if (continueAttack) {
					attackStage += 2;
				}
				else
					attackStage++;
				y2 = y;
				return attack(gamer);
			}
			else if (checkIfShip(y2 + 1, x2, gamer))
			{
				shotgrid[y2 + 1][x2] = '$';
				gamer.setHitChar(y2 + 1, x2);
				if (gamer.checkIfSink()) {
					gamer.displayInfo("Computer " + name + ": oponent ship sink");
					attackStage = 0;
					continueAttack = false;
					return true;
				}
				gamer.displayInfo("Computer " + name + ": oponent ship hit");
				y2 += 1;
				continueAttack = true;
				return true;
			}
			else
			{
				shotgrid[y2 + 1][x2] = 'X';
				gamer.setMissChar(y2 + 1, x2);
				gamer.displayInfo("Computer " + name + ": miss");
				if (continueAttack) {
					attackStage += 2;
				}
				else
					attackStage++;
				y2 = y;
				return false;
			}
		}
	}
	else if (attackStage == 3)
	{
		if (x2 - 1 == -1 && !continueAttack)
		{
			attackStage++;
			x2 = x;
			return attack(gamer);
		}
		else if (x2 - 1 == -1 && continueAttack)
		{
			attackStage = 0;
			x2 = x;
			return attack(gamer);
		}
		else
		{
			if (!checkShotGrid(y2, x2 - 1)) {
				if (continueAttack) {
					attackStage = 0;
				}
				else
					attackStage++;
				x2 = x;
				return attack(gamer);
			}
			else if (checkIfShip(y2, x2 - 1, gamer))
			{
				shotgrid[y2][x2 - 1] = '$';
				gamer.setHitChar(y2, x2 - 1);
				if (gamer.checkIfSink()) {
					gamer.displayInfo("Computer " + name + ": oponent ship sink");
					attackStage = 0;
					continueAttack = false;
					return true;
				}
				gamer.displayInfo("Computer " + name + ": oponent ship hit");
				x2 -= 1;
				return true;
			}
			else
			{
				shotgrid[y2][x2 - 1] = 'X';
				gamer.setMissChar(y2, x2 - 1);
				gamer.displayInfo("Computer " + name + ": miss");
				if (continueAttack) {
					attackStage = 0;
					continueAttack = false;
				}
				else
					attackStage++;
				x2 = x;
				return false;
			}
		}
	}
	else if (attackStage == 4)
	{
		continueAttack = false;
		if (y2 - 1 == -1)
		{
			attackStage = 0;
			return attack(gamer);
		}
		else
		{
			if (!checkShotGrid(y2 - 1, x2)) {
				attackStage = 0;
				y2 = y;
				return attack(gamer);
			}
			else if (checkIfShip(y2 - 1, x2, gamer))
			{
				shotgrid[y2 - 1][x2] = '$';
				gamer.setHitChar(y2 - 1, x2);
				if (gamer.checkIfSink()) {
					gamer.displayInfo("Computer " + name + ": oponent ship sink");
					attackStage = 0;
					continueAttack = false;
					return true;
				}
				gamer.displayInfo("Computer " + name + ": oponent ship hit");
				y2 -= 1;
				return true;
			}
			else
			{
				shotgrid[y2 - 1][x2] = 'X';
				gamer.setMissChar(y2 - 1, x2);
				gamer.displayInfo("Computer " + name + ": miss");
				attackStage = 0;
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
