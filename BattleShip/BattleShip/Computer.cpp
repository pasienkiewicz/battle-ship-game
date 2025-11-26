#include "Computer.h"

Computer::Computer(bool advancedShipSpawn, bool advancedAttack)
{
	this->name = "Computer";
	this->advancedShipSpawn = advancedShipSpawn;
	this->advancedAttack = advancedAttack;

	shipSize[0] = 5;
	shipSize[1] = 4;
	shipSize[2] = 3;
	shipSize[3] = 3;
	shipSize[4] = 2;

	automaticShipSpawn();
}

bool Computer::attack(Ships &player)
{
	if (nextAttackContext.has_value())
	{
		AttackContext ctx = *nextAttackContext;
		nextAttackContext = std::nullopt;

		return attack(player, ctx);
	}

	return attack(player, getDefaultAttackContext());
}

bool Computer::attack(Ships &player, AttackContext attackContext)
{
	Coordinates attactCoordinates = attackContext.shotCoordinates;
	AttackDirection attackDirection = attackContext.attackDirection;

	if (!isShotAttemptValid(attactCoordinates))
	{
		return attack(player, getNextAttactContextOnFailedAttempt(attackContext));
	}

	if (!didHitShip(attactCoordinates, player))
	{
		player.setMissChar(attactCoordinates);
		shotgrid[attactCoordinates.y][attactCoordinates.x] = 'X';
		player.displayInfo(name + ": miss");

		nextAttackContext.emplace(getNextAttactContextOnFailedAttempt(attackContext));

		return false;
	}

	shotgrid[attactCoordinates.y][attactCoordinates.x] = '$';
	player.setHitChar(attactCoordinates);
	if (player.checkIfSink())
	{
		player.displayInfo(name + ": oponent ship sink");

		nextAttackContext.emplace(getDefaultAttackContext());

		return true;
	}
	player.displayInfo(name + ": oponent ship hit");

	if (AttackDirection::NONE == attackDirection)
	{
		return attack(player, AttackContext(AttackDirection::RIGHT, Coordinates(attactCoordinates.x + 1, attactCoordinates.y), true));
	}

	if (AttackDirection::RIGHT == attackDirection)
	{
		return attack(player, AttackContext(AttackDirection::RIGHT, Coordinates(attactCoordinates.x + 1, attactCoordinates.y), true));
	}

	if (AttackDirection::DOWN == attackDirection)
	{
		return attack(player, AttackContext(AttackDirection::DOWN, Coordinates(attactCoordinates.x, attactCoordinates.y + 1), true));
	}

	if (AttackDirection::LEFT == attackDirection)
	{
		return attack(player, AttackContext(AttackDirection::LEFT, Coordinates(attactCoordinates.x - 1, attactCoordinates.y), true));
	}

	if (AttackDirection::LEFT == attackDirection)
	{
		return attack(player, AttackContext(AttackDirection::LEFT, Coordinates(attactCoordinates.x, attactCoordinates.y - 1), true));
	}

	return attack(player, getDefaultAttackContext());
}

Coordinates Computer::getValidAttackCoordinates()
{
	Coordinates coordinates = getAttackCoordinates();
	if (isShotAttemptValid(coordinates))
	{
		return coordinates;
	}

	return getValidAttackCoordinates();
}

Coordinates Computer::getAttackCoordinates()
{
	if (advancedAttack)
	{
		Coordinates coordinates = Coordinates(rand() % getcolumns(), rand() % getrows());
		if ((coordinates.y + coordinates.x) % 2 != 0)
		{
			return getAttackCoordinates();
		}
	}

	return Coordinates(rand() % getcolumns(), rand() % getrows());
}

AttackContext Computer::getNextAttactContextOnFailedAttempt(AttackContext currentAttackContext)
{
	Coordinates attactCoordinates = currentAttackContext.shotCoordinates;
	AttackDirection attackDirection = currentAttackContext.attackDirection;
	bool continueAttackInSameDirection = currentAttackContext.continueAttackInSameDirection;

	if (AttackDirection::RIGHT == attackDirection)
	{
		return continueAttackInSameDirection
				   ? AttackContext(AttackDirection::LEFT, Coordinates(attactCoordinates.x - 2, attactCoordinates.y), true)
				   : AttackContext(AttackDirection::DOWN, Coordinates(attactCoordinates.x - 1, attactCoordinates.y + 1), false);
	}

	if (AttackDirection::DOWN == attackDirection)
	{
		return continueAttackInSameDirection
				   ? AttackContext(AttackDirection::UP, Coordinates(attactCoordinates.x, attactCoordinates.y - 2), true)
				   : AttackContext(AttackDirection::DOWN, Coordinates(attactCoordinates.x - 1, attactCoordinates.y + 1), false);
	}

	if (AttackDirection::LEFT == attackDirection)
	{
		return AttackContext(AttackDirection::UP, Coordinates(attactCoordinates.x + 1, attactCoordinates.y - 1), true);
	}

	return getDefaultAttackContext();
}

AttackContext Computer::getDefaultAttackContext()
{
	return AttackContext(AttackDirection::NONE, getValidAttackCoordinates(), false);
}