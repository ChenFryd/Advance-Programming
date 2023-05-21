/*
 * Wolf.h
 *
 *  Created on: 29 Dec 2021
 *      Author: user
 */

#ifndef WOLF_H_
#define WOLF_H_

#include "Creature.h"

class Wolf: public Creature {
public:
	Wolf(): Creature() {};
	virtual ~Wolf(){};
	virtual std::string getType();
	virtual void fight(Creature &c);
	virtual void drinkHealth();
	virtual void drinkPoison();
	virtual void drinkBeer();
};

#endif /* WOLF_H_ */
