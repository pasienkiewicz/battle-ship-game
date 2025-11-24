#include <iostream>
#include "Board.h"
#include "IO.h"
#include "Player.h"
#include "Computer.h"
#include <time.h>
#include <chrono>
#include <thread>

string askForComputerName()
{
	string answer = IO::askForInput("Do you want to give a name to Computer? (y/n): ");
	if (answer != "y")
	{
		return "Computer";
	}

	return IO::askForInput("Name: ");
}

string askForPlayerName()
{
	string answer = IO::askForInput("Do you want to give a name to Player? (y/n): ");
	if (answer != "y")
	{
		return "Player";
	}

	return IO::askForInput("Name: ");
}

int main()
{
	srand(time(NULL));
	Player gamer;
	Computer ai;
	string temp;

	gamer.name = askForPlayerName();
	ai.name = askForComputerName();

	cout << "Do you want to Computer ships to be placed in advanced way with spaces? (y/n): ";
	cin >> temp;
	if (temp == "y")
		ai.advancedShipSpawn = true;

	cout << "Do you want to Computer to attack in advanced way? (y/n): ";
	cin >> temp;
	if (temp == "y")
		ai.advancedAttack = true;

	ai.automaticShipSpawn();

	cout << "Do you want to your to be placed randomly? (y/n): ";
	cin >> temp;
	if (temp == "y")
	{
		cout << "Do you want to your ship be placed in advanced way with spaces? (y/n): ";
		cin >> temp;
		if (temp == "y")
		{
			gamer.advancedShipSpawn = true;
		}
		gamer.automaticShipSpawn();
	}
	else
		gamer.spawnShip();

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
