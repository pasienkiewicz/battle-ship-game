#pragma once
#include "AttackDirection.h"
#include "Coordinates.h"

struct AttackContext
{
    const AttackDirection attackDirection;
    const Coordinates shotCoordinates;

    AttackContext(AttackDirection attackDirection, Coordinates shotCoordinates)
        : attackDirection(attackDirection), shotCoordinates(shotCoordinates)
    {
    }
};
