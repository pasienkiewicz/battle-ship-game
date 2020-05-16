#pragma once
#include "Ships.h"
#include "Computer.h"
class Player: public Ships
{
public:
	//konstructor
	Player();
	//acess point
	bool attack(Ships& oponentShip);
private:
	//methods whith diferent classes
private:
	void spawnShip();
	void convertCoordinates(string a, string b);
	void convertCoordinates(string a);
	bool checkDoubleCoordinates();
	bool checkCoordinates();
	bool checkSize(int i);
	bool checkDirection();
	int encript(char a);
private:
	//variables
	int x, y, x2, y2;
	string shipsType[5];
};

