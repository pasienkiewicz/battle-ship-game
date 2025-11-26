#pragma once
#include "AttackDirection.h"
#include "Ships.h"
#include "Player.h"
#include "AttackContext.h"

class Computer : public Ships
{
public:
	Computer(bool advancedShipSpawn, bool advancedAttack);
	Coordinates getValidAttackCoordinates();
	bool attack(Ships &player);

private:
	bool advancedAttack = false;
	optional<AttackContext> nextAttackContext = nullopt;

	bool attack(Ships &player, AttackContext nextAttackContext);
	Coordinates getAttackCoordinates();
	AttackContext getDefaultAttackContext();
	AttackContext getNextAttactContextOnFailedAttempt(AttackContext currentAttackContext);
};
