#pragma once
#include "Ships.h"
#include "Computer.h"
class Player : public Ships
{
public:
	Player();
	bool attack(Ships &oponentShip);
	void spawnShip();

private:
	void convertCoordinates(string a, string b);
	void convertCoordinates(string a);
	bool areDoubleCoordinatesValid();
	bool areCoordinatesValid();
	bool isShipCorrectSize(int i);
	bool getShipDirection();
	int transformCharToInt(char a);

private:
	int x, y, x2, y2;
	string shipsType[5];
};
