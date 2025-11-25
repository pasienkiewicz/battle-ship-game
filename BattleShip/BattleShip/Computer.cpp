#include "Computer.h"

Computer::Computer(bool advancedShipSpawn, bool advancedAttack)
{
	this->name = "Computer";
	this->advancedShipSpawn = advancedShipSpawn;
	this->advancedAttack = advancedAttack;

	shipSize[0] = 5;
	shipSize[1] = 4;
	shipSize[2] = 3;
	shipSize[3] = 3;
	shipSize[4] = 2;

	automaticShipSpawn();
}

bool Computer::attack(Ships &player)
{
	if (attackStage == 0)
	{
		while (true)
		{
			if (advancedAttack)
			{
				y = rand() % getcolumns();
				x = rand() % getrows();
				if ((y + x) % 2 != 0)
					continue;
			}
			else
			{
				y = rand() % getcolumns();
				x = rand() % getrows();
			}

			if (isHitAttemptValid(y, x))
			{
				if (didHitShip(y, x, player))
				{
					shotgrid[y][x] = '$';
					player.setHitChar(y, x);
					if (player.checkIfSink())
					{
						player.displayInfo(name + ": oponent ship sink");
						attackStage = 0;
						continueAttack = false;
						return true;
					}
					player.displayInfo(name + ": oponent ship hit");
					attackStage++;
					x2 = x;
					y2 = y;
					return true;
				}
				else
				{
					player.setMissChar(y, x);
					shotgrid[y][x] = 'X';
					player.displayInfo(name + ": miss");
					return false;
				}
			}
		}
	}
	else if (attackStage == 1)
	{
		if (x2 + 1 == getrows() && !continueAttack)
		{
			attackStage++;
			x2 = x;
			return attack(player);
		}
		else if (x2 + 1 == getrows() && continueAttack)
		{
			attackStage += 2;
			x2 = x;
			return attack(player);
		}
		else
		{
			if (!isHitAttemptValid(y2, x2 + 1))
			{
				if (continueAttack)
				{
					attackStage += 2;
				}
				else
					attackStage++;
				x2 = x;
				return attack(player);
			}
			else if (didHitShip(y2, x2 + 1, player))
			{
				shotgrid[y2][x2 + 1] = '$';
				player.setHitChar(y2, x2 + 1);
				if (player.checkIfSink())
				{
					player.displayInfo(name + ": oponent ship sink");
					attackStage = 0;
					continueAttack = false;
					return true;
				}
				player.displayInfo(name + ": oponent ship hit");
				x2 += 1;
				continueAttack = true;
				return true;
			}
			else
			{
				shotgrid[y2][x2 + 1] = 'X';
				player.setMissChar(y2, x2 + 1);
				player.displayInfo(name + ": miss");
				if (continueAttack)
				{
					attackStage += 2;
				}
				else
					attackStage++;
				x2 = x;
				return false;
			}
		}
	}
	else if (attackStage == 2)
	{
		if (y2 + 1 == getcolumns() && !continueAttack)
		{
			attackStage++;
			y2 = y;
			return attack(player);
		}
		else if (y2 + 1 == getcolumns() && continueAttack)
		{
			attackStage += 2;
			y2 = y;
			return attack(player);
		}
		else
		{
			if (!isHitAttemptValid(y2 + 1, x2))
			{
				if (continueAttack)
				{
					attackStage += 2;
				}
				else
					attackStage++;
				y2 = y;
				return attack(player);
			}
			else if (didHitShip(y2 + 1, x2, player))
			{
				shotgrid[y2 + 1][x2] = '$';
				player.setHitChar(y2 + 1, x2);
				if (player.checkIfSink())
				{
					player.displayInfo(name + ": oponent ship sink");
					attackStage = 0;
					continueAttack = false;
					return true;
				}
				player.displayInfo(name + ": oponent ship hit");
				y2 += 1;
				continueAttack = true;
				return true;
			}
			else
			{
				shotgrid[y2 + 1][x2] = 'X';
				player.setMissChar(y2 + 1, x2);
				player.displayInfo(name + ": miss");
				if (continueAttack)
				{
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
			return attack(player);
		}
		else if (x2 - 1 == -1 && continueAttack)
		{
			attackStage = 0;
			x2 = x;
			return attack(player);
		}
		else
		{
			if (!isHitAttemptValid(y2, x2 - 1))
			{
				if (continueAttack)
				{
					attackStage = 0;
				}
				else
					attackStage++;
				x2 = x;
				return attack(player);
			}
			else if (didHitShip(y2, x2 - 1, player))
			{
				shotgrid[y2][x2 - 1] = '$';
				player.setHitChar(y2, x2 - 1);
				if (player.checkIfSink())
				{
					player.displayInfo(name + ": oponent ship sink");
					attackStage = 0;
					continueAttack = false;
					return true;
				}
				player.displayInfo(name + ": oponent ship hit");
				x2 -= 1;
				return true;
			}
			else
			{
				shotgrid[y2][x2 - 1] = 'X';
				player.setMissChar(y2, x2 - 1);
				player.displayInfo(name + ": miss");
				if (continueAttack)
				{
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
			return attack(player);
		}
		else
		{
			if (!isHitAttemptValid(y2 - 1, x2))
			{
				attackStage = 0;
				y2 = y;
				return attack(player);
			}
			else if (didHitShip(y2 - 1, x2, player))
			{
				shotgrid[y2 - 1][x2] = '$';
				player.setHitChar(y2 - 1, x2);
				if (player.checkIfSink())
				{
					player.displayInfo(name + ": oponent ship sink");
					attackStage = 0;
					continueAttack = false;
					return true;
				}
				player.displayInfo(name + ": oponent ship hit");
				y2 -= 1;
				return true;
			}
			else
			{
				shotgrid[y2 - 1][x2] = 'X';
				player.setMissChar(y2 - 1, x2);
				player.displayInfo(name + ": miss");
				attackStage = 0;
				y2 = y;
				return false;
			}
		}
	}

	throw invalid_argument("Invalid attack stage");
}
