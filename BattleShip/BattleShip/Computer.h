#pragma once
#include "Ships.h"
#include "Player.h"

class Computer : public Ships
{
public:
	Computer(bool advancedShipSpawn, bool advancedAttack);
	bool attack(Ships &gamer);

public:
	bool advancedAttack = false;

private:
	bool continueAttack;
	int attackStage = 0;

	int x, y, x2, y2;
	bool downright;
};
