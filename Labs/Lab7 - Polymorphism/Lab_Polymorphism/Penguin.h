/*
 * Penguin.h
 *
 *  Created on: 29 Dec 2021
 *      Author: user
 */

#ifndef PENGUIN_H_
#define PENGUIN_H_

#include "Creature.h"

class Penguin: public Creature {
public:
	Penguin(): Creature() {};
	virtual ~Penguin(){};
	virtual std::string getType();
	virtual void fight(Creature &c);
	virtual void drinkHealth();
	virtual void drinkPoison();
	virtual void drinkBeer();
};

#endif /* PENGUIN_H_ */
