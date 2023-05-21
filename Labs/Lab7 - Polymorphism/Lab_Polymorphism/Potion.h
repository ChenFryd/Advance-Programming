/*
 * Potion.h
 *
 *  Created on: 5 Jan 2022
 *      Author: user
 */

#ifndef POTION_H_
#define POTION_H_
class Creature;

class Potion {
public:
	Potion(){};
	virtual ~Potion(){};
	virtual void drink(Creature &c) = 0;
};

#endif /* POTION_H_ */
