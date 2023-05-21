/*
 * Poison.cpp
 *
 *  Created on: 5 Jan 2022
 *      Author: user
 */

#include "Poison.h"
#include "Creature.h"

void Poison::drink(Creature& c)
{
	c.drinkPoison();
}
