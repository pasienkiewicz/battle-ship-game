#pragma once
#include "Ships.h"
#include "Player.h"

class Computer : public Ships
{
public:
	Computer();
	bool attack(Ships &gamer);

public:
	bool advancedAttack = false;

private:
	bool continueAttack;
	int attackStage;

	int x, y, x2, y2;
	bool downright;
};
