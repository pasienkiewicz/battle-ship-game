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
		AttackContext nextAttackContext = getNextAttactContextOnFailedAttempt(attackContext);
		previousAttackDirection = attackDirection;

		return attack(player, nextAttackContext);
	}

	if (!didHitShip(attactCoordinates, player))
	{
		player.setMissChar(attactCoordinates);
		shotgrid[attactCoordinates.y()][attactCoordinates.x()] = 'X';
		player.displayInfo(name + ": miss");

		nextAttackContext.emplace(getNextAttactContextOnFailedAttempt(attackContext));

		return false;
	}

	shotgrid[attactCoordinates.y()][attactCoordinates.x()] = '$';
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
		if (Coordinates::areValid(attactCoordinates.x() + 1, attactCoordinates.y()))
		{
			previousAttackDirection = AttackDirection::NONE;

			return attack(player, AttackContext(AttackDirection::RIGHT, Coordinates(attactCoordinates.x() + 1, attactCoordinates.y())));
		}

		AttackContext nextAttackContext = getNextAttactContextOnFailedAttempt(attackContext);
		previousAttackDirection = AttackDirection::NONE;

		return attack(player, nextAttackContext);
	}

	if (AttackDirection::RIGHT == attackDirection)
	{
		if (Coordinates::areValid(attactCoordinates.x() + 1, attactCoordinates.y()))
		{
			previousAttackDirection = AttackDirection::RIGHT;

			return attack(player, AttackContext(AttackDirection::RIGHT, Coordinates(attactCoordinates.x() + 1, attactCoordinates.y())));
		}

		AttackContext nextAttackContext = getNextAttactContextOnFailedAttempt(attackContext);
		previousAttackDirection = AttackDirection::RIGHT;

		return attack(player, nextAttackContext);
	}

	if (AttackDirection::DOWN == attackDirection)
	{
		if (Coordinates::areValid(attactCoordinates.x(), attactCoordinates.y() + 1))
		{
			previousAttackDirection = AttackDirection::DOWN;

			return attack(player, AttackContext(AttackDirection::DOWN, Coordinates(attactCoordinates.x(), attactCoordinates.y() + 1)));
		}

		AttackContext nextAttackContext = getNextAttactContextOnFailedAttempt(attackContext);
		previousAttackDirection = AttackDirection::DOWN;

		return attack(player, nextAttackContext);
	}

	if (AttackDirection::LEFT == attackDirection)
	{
		if (Coordinates::areValid(attactCoordinates.x() - 1, attactCoordinates.y()))
		{
			previousAttackDirection = AttackDirection::LEFT;

			return attack(player, AttackContext(AttackDirection::LEFT, Coordinates(attactCoordinates.x() - 1, attactCoordinates.y())));
		}

		AttackContext nextAttackContext = getNextAttactContextOnFailedAttempt(attackContext);
		previousAttackDirection = AttackDirection::LEFT;

		return attack(player, nextAttackContext);
	}

	if (Coordinates::areValid(attactCoordinates.x(), attactCoordinates.y() - 1))
	{
		previousAttackDirection = AttackDirection::UP;

		return attack(player, AttackContext(AttackDirection::UP, Coordinates(attactCoordinates.x(), attactCoordinates.y() - 1)));
	}

	previousAttackDirection = AttackDirection::NONE;

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
		if ((coordinates.y() + coordinates.x()) % 2 != 0)
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

	if (AttackDirection::RIGHT == attackDirection)
	{
		if (AttackDirection::RIGHT != previousAttackDirection && Coordinates::areValid(attactCoordinates.x() - 1, attactCoordinates.y() + 1))
		{
			return AttackContext(AttackDirection::DOWN, Coordinates(attactCoordinates.x() - 1, attactCoordinates.y() + 1));
		}

		optional<Coordinates> coordinates = getNearestValidCoordinates(Coordinates(attactCoordinates.x() - 2, attactCoordinates.y()), AttackDirection::LEFT);
		if (!coordinates.has_value())
		{
			return getDefaultAttackContext();
		}

		return AttackContext(AttackDirection::LEFT, *coordinates);
	}

	if (AttackDirection::DOWN == attackDirection)
	{
		if (AttackDirection::DOWN != previousAttackDirection && Coordinates::areValid(attactCoordinates.x() - 1, attactCoordinates.y() - 1))
		{
			return AttackContext(AttackDirection::LEFT, Coordinates(attactCoordinates.x() - 1, attactCoordinates.y() - 1));
		}

		optional<Coordinates> coordinates = getNearestValidCoordinates(Coordinates(attactCoordinates.x(), attactCoordinates.y() - 2), AttackDirection::UP);
		if (!coordinates.has_value())
		{
			return getDefaultAttackContext();
		}

		return AttackContext(AttackDirection::UP, *coordinates);
	}

	if (AttackDirection::LEFT == attackDirection)
	{
		if (
			!(AttackDirection::LEFT == previousAttackDirection || AttackDirection::RIGHT == previousAttackDirection) &&
			Coordinates::areValid(attactCoordinates.x() + 1, attactCoordinates.y() - 1))
		{
			return AttackContext(AttackDirection::UP, Coordinates(attactCoordinates.x() + 1, attactCoordinates.y() - 1));
		}
	}

	return getDefaultAttackContext();
}

AttackContext Computer::getDefaultAttackContext()
{
	return AttackContext(AttackDirection::NONE, getValidAttackCoordinates());
}

optional<Coordinates> Computer::getNearestValidCoordinates(Coordinates attackCoordinates, AttackDirection attackDirection)
{
	if (isShotAttemptValid(attackCoordinates))
	{
		return attackCoordinates;
	}

	if (AttackDirection::LEFT == attackDirection)
	{
		if (!Coordinates::areValid(attackCoordinates.x() - 1, attackCoordinates.y()))
		{
			return nullopt;
		}

		return getNearestValidCoordinates(Coordinates(attackCoordinates.x() - 1, attackCoordinates.y()), AttackDirection::LEFT);
	}

	if (AttackDirection::UP == attackDirection)
	{
		if (!Coordinates::areValid(attackCoordinates.x(), attackCoordinates.y() - 1))
		{
			return nullopt;
		}

		return getNearestValidCoordinates(Coordinates(attackCoordinates.x(), attackCoordinates.y() - 1), AttackDirection::LEFT);
	}

	return nullopt;
}