#pragma once
#include <utility>
#include <optional>
#include "Ships.h"
#include "Coordinates.h"
#include "Computer.h"

class Player : public Ships
{
public:
	Player();
	bool attack(Ships &oponentShip);
	void spawnShip();

private:
	Coordinates convertCoordinates(string a);
	bool areDoubleCoordinatesValid();
	bool areCoordinatesValid();
	bool isShipCorrectSize(Coordinates firstCoordinates, Coordinates secondCoordinates, int i);
	bool getShipDirection(Coordinates firstCoordinates, Coordinates secondCoordinates);
	int transformCharToInt(char a);

private:
	string shipsType[5];
};
