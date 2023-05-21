/*
 * Creature.h
 *
 *  Created on: 29 Dec 2021
 *      Author: user
 */

#ifndef CREATURE_H_
#define CREATURE_H_
#include <string>
#include <iostream>
using namespace std;
//#include "Potion.h"
class Potion;

class Creature {
private:
	static const int MAX_HEALTH = 100;
protected:
	int health_stat;
public:
	Creature(): health_stat(MAX_HEALTH) {};
	virtual ~Creature() {};
	void hurtHealth(int amount);
	void gainHealth(int amount);
	virtual std::string getType() = 0;
	virtual void fight(Creature &c) = 0;
	virtual void drinkHealth() = 0;
	virtual void drinkPoison() = 0;
	virtual void drinkBeer() = 0;

};

#endif /* CREATURE_H_ */
