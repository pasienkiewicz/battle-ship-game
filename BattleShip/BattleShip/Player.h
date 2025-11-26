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
	bool isShipCorrectSize(Coordinates firstCoordinates, Coordinates secondCoordinates, int i);
	bool getShipDirection(Coordinates firstCoordinates, Coordinates secondCoordinates);

private:
	string shipsType[5];
};
