/*
 * Troll.h
 *
 *  Created on: 29 Dec 2021
 *      Author: user
 */

#ifndef TROLL_H_
#define TROLL_H_

#include "Creature.h"

class Troll: public Creature {
public:
	Troll(): Creature() {};
	virtual ~Troll(){};
	virtual std::string getType();
	virtual void fight(Creature &c);
	virtual void drinkHealth();
	virtual void drinkPoison();
	virtual void drinkBeer();
};

#endif /* TROLL_H_ */
