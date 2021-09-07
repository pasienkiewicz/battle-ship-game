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