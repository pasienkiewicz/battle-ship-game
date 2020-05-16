#pragma once
#include <set>
#include "Board.h"
class Ships: public Board
{
public:
	Ships();
	char getAttackedChar(int y, int x);
	bool checkLost();
	void setChar(int y, int x);
	bool checkIfSink();
public:
	//options
	void automaticShipSpawn();
protected:
	bool checkShotGrid(int y, int x);
	void setShip(int y, int x, bool direction, int shipSize, char shipType);
	bool checkIfShip(int y, int x, Ships& oponentShip);
	bool checkOverlap(int y, int x, bool direction, int shipSize);
protected:
	string name;
	const int TotalnumberOfShips = 5;
	int numberOfShips;
	int shipSize[5];
	int shipType[5];
};

