#pragma once
#include <set>
#include "Board.h"
class Ships: public Board
{
public:
	Ships();
	char getAttackedChar(int y, int x);
	bool checkLost();
	void setHitChar(int y, int x);
	void setMissChar(int y, int x);
	bool checkIfSink();
public:
	//options methods
	void automaticShipSpawn();
public:
	// options variables
	bool advancedShipSpawn = false;
	string name = "X";
protected:
	bool checkShotGrid(int y, int x);
	void setShip(int y, int x, bool direction, int shipSize, char shipType);
	bool checkIfShip(int y, int x, Ships& oponentShip);
	bool checkOverlap(int y, int x, bool direction, int shipSize);
protected:
	int numberOfShips = 5;
	int shipSize[5];
	char shipType[5];
};

