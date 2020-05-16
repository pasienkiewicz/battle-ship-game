#pragma once
#include "Ships.h"
#include "Player.h"
class Computer: public Ships
{
public:
	//konstructor
	Computer();
	//acess point
	int state;
	bool attack(Ships& gamer);
private:
	bool inicialRecursion(Ships& gamer);
private:
	int step;
	int x, y, x2, y2;
	bool downright;

	
};

