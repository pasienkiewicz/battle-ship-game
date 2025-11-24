#pragma once
#include "Ships.h"
#include "Computer.h"
class Player : public Ships
{
public:
	Player();
	bool attack(Ships &oponentShip);
	void spawnShip();

public: // options
	string name = "X";

private:
private:
	void convertCoordinates(string a, string b);
	void convertCoordinates(string a);
	bool checkDoubleCoordinates();
	bool checkCoordinates();
	bool checkSize(int i);
	bool checkDirection();
	int encript(char a);

private:
	int x, y, x2, y2;
	string shipsType[5];
};
