#pragma once
#include "AttackDirection.h"
#include "Coordinates.h"

struct AttackContext
{
    const AttackDirection attackDirection;
    const Coordinates shotCoordinates;
    const bool continueAttackInSameDirection;

    AttackContext(AttackDirection attackDirection, Coordinates shotCoordinates, bool continueAttackInSameDirection)
        : attackDirection(attackDirection), shotCoordinates(shotCoordinates), continueAttackInSameDirection(continueAttackInSameDirection)
    {
    }
};
