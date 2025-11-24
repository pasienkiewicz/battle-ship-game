#include <iostream>
#include "Board.h"
#include "IO.h"
#include "Player.h"
#include "Computer.h"
#include <time.h>
#include <chrono>
#include <thread>

using namespace std;

string askForPlayerName()
{
	string answer = IO::askForInput("Do you want to give a name to Player? (y/n): ");
	if (answer != "y")
	{
		return "Player";
	}

	return IO::askForInput("Name: ");
}

bool askIfCompuerShipsNeedsToBePlayedInAdvancedWay()
{
	string answer = IO::askForInput("Do you want to Computer ships to be placed in advanced way with spaces? (y/n): ");

	return answer == "y";
}

bool askIfComputerAttacksInAdvancedWay()
{
	string answer = IO::askForInput("Do you want the Computer to attack in advanced way? (y/n): ");

	return answer == "y";
}

void spawnPlayerShips(Player &gamer)
{
	string answer = IO::askForInput("Do you want to put your ships yourself? (y/n): ");
	if (answer == "y")
	{
		gamer.spawnShip();

		return;
	}

	answer = IO::askForInput("Do you want to your ships to be placed in advanced way with spaces? (y/n): ");

	gamer.advancedShipSpawn = answer == "y";

	gamer.automaticShipSpawn();
}

int main()
{
	srand(time(NULL));
	Player gamer = Player(askForPlayerName());

	Computer ai = Computer(askIfCompuerShipsNeedsToBePlayedInAdvancedWay(), askIfComputerAttacksInAdvancedWay());

	spawnPlayerShips(gamer);

	while (true)
	{
		while (gamer.attack(ai))
		{
			if (ai.checkLost())
			{
				gamer.drawTwoBoards(ai, "Player " + gamer.name + "Have won");
				return 0;
			}
		}
		gamer.drawTwoBoards(ai);
		while (ai.attack(gamer))
		{
			this_thread::sleep_for(chrono::seconds(2));

			if (gamer.checkLost())
			{
				gamer.drawTwoBoards(ai, "Computer " + ai.name + ": Have won");
				return 0;
			}
			gamer.drawTwoBoards(ai);
		}
		this_thread::sleep_for(chrono::seconds(2));
		gamer.drawTwoBoards(ai);
	}
}
