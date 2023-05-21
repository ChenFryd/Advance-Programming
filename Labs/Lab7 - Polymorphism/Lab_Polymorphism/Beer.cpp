/*
 * Beer.cpp
 *
 *  Created on: 5 Jan 2022
 *      Author: user
 */

#include "Beer.h"
#include "Creature.h"

void Beer::drink(Creature &c)
{
	c.drinkBeer();
}
