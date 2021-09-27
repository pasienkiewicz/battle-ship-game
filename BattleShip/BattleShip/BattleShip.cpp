#include <iostream>
#include "Board.h"
#include "Player.h"
#include "Computer.h"
#include <time.h>
#include <chrono>
#include <thread>


int main() 
{
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	srand(time(NULL));
	Player gamer;
	Computer ai;
	string temp;

	cout << "Do you want to give a name to Computer? (y/n): ";
	cin >> temp;
	if (temp == "y") {
		cout << "Name: ";
		cin >> temp;
		ai.name = temp;
	}

	cout << "Do you want to give a name to Player? (y/n): ";
	cin >> temp;
	if (temp == "y") {
		cout << "Name: ";
		cin >> temp;
		gamer.name = temp;
	}
		
	cout << "Do you want to Computer ships to be placed in advanced way with spaces? (y/n): ";
	cin >> temp;
	if (temp == "y") ai.advancedShipSpawn = true;

	cout << "Do you want to Computer to attack in advanced way? (y/n): ";
	cin >> temp;
	if (temp == "y") ai.advancedAttack == true;

	ai.automaticShipSpawn();

	cout << "Do you want to your to be placed randomly? (y/n): ";
	cin >> temp;
	if (temp == "y") {
		cout << "Do you want to your ship be placed in advanced way with spaces? (y/n): ";
		cin >> temp;
		if (temp == "y") {
			gamer.advancedShipSpawn = true;
		}
		gamer.automaticShipSpawn();
	}
	else
		gamer.spawnShip();

	while (true)
	{
		while(gamer.attack(ai))
		{
			if (ai.checkLost())
			{
				gamer.drawTwoBoards(ai, "Player " + gamer.name + "Have won");
				return 0;
			}
		}
		gamer.drawTwoBoards(ai);
		while(ai.attack(gamer))
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