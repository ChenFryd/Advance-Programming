/*
 * Health.cpp
 *
 *  Created on: 5 Jan 2022
 *      Author: user
 */

#include "Health.h"
#include "Creature.h"

void Health::drink(Creature &c)
{
	c.drinkHealth();
}
