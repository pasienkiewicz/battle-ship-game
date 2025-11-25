#include <iostream>
#include "Board.h"
#include "IO.h"
#include "Player.h"
#include "Computer.h"
#include <time.h>
#include <chrono>
#include <thread>

using namespace std;

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

void spawnPlayerShips(Player &player)
{
	string answer = IO::askForInput("Do you want to put your ships yourself? (y/n): ");
	if (answer == "y")
	{
		player.spawnShip();

		return;
	}

	answer = IO::askForInput("Do you want to your ships to be placed in advanced way with spaces? (y/n): ");

	player.advancedShipSpawn = answer == "y";

	player.automaticShipSpawn();
}

int main()
{
	srand(time(NULL));
	Player player = Player();

	Computer computer = Computer(askIfCompuerShipsNeedsToBePlayedInAdvancedWay(), askIfComputerAttacksInAdvancedWay());

	spawnPlayerShips(player);

	while (true)
	{
		while (player.attack(computer))
		{
			if (computer.checkLost())
			{
				player.drawTwoBoards(computer, player.name + "Have won");
				return 0;
			}
		}
		player.drawTwoBoards(computer);
		while (computer.attack(player))
		{
			this_thread::sleep_for(chrono::seconds(1));

			if (player.checkLost())
			{
				player.drawTwoBoards(computer, computer.name + ": Have won");
				return 0;
			}
			player.drawTwoBoards(computer);
		}
		this_thread::sleep_for(chrono::seconds(1));
		player.drawTwoBoards(computer);
	}
}
