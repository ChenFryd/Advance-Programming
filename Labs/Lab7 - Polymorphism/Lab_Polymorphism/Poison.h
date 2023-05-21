/*
 * Poison.h
 *
 *  Created on: 5 Jan 2022
 *      Author: user
 */

#ifndef POISON_H_
#define POISON_H_

#include "Potion.h"
//#include "Creature.h"

class Poison: public Potion {
public:
	Poison(): Potion(){};
	virtual ~Poison(){};
	virtual void drink(Creature& c);
};

#endif /* POISON_H_ */
