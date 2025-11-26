#pragma once
#include <set>
#include "Board.h"
#include "Coordinates.h"

class Ships : public Board
{
public:
	Ships();
	char getAttackedChar(Coordinates coordinates);
	bool checkLost();
	void setHitChar(Coordinates coordinates);
	void setMissChar(Coordinates coordinates);
	bool checkIfSink();

public:
	void automaticShipSpawn();

public:
	bool advancedShipSpawn = false;
	string name = "X";

protected:
	bool isShotAttemptValid(Coordinates coordinates);
	void setShip(Coordinates coordinates, bool direction, int shipSize, char shipType);
	bool didHitShip(Coordinates coordinates, Ships &oponentShip);
	bool isShipPlacedInCorrectPossition(Coordinates coordinates, bool direction, int shipSize);

protected:
	int numberOfShips = 5;
	int shipSize[5];
	char shipType[5];
};
