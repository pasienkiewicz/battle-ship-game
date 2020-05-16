#include <iostream>
#include "Board.h"
#include "Player.h"
#include "Computer.h"
#include <Windows.h>
#include <time.h>


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
			if (ai.checkIfSink())
			{
				gamer.info1= "Oponent ship sinked";
			}
			else
			{
				gamer.info1= "Oponent ship hited";
			}
			if (ai.checkLost())
			{
				gamer.info1= "You have won";
				gamer.drawTwoBoards();
				return 0;
			}
		}
		gamer.info1 = "Oponent ship missed";
		if(ai.attack(gamer))
		{
			if (gamer.checkIfSink)
			{
				gamer.info2 = "Oponent ship sinked";
				ai.state = 0;
			}
			else
			{
				gamer.info2 = "Oponent ship hited";
			}
			if (gamer.checkLost())
			{
				gamer.info2 = "You have lost";
			}
			
		}

	}
	
}