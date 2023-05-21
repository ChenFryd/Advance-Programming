/*
 * Health.h
 *
 *  Created on: 5 Jan 2022
 *      Author: user
 */

#ifndef HEALTH_H_
#define HEALTH_H_

#include "Potion.h"

class Health: public Potion {
public:
	Health(): Potion(){};
	virtual ~Health() {};
	virtual void drink(Creature &c);
};

#endif /* HEALTH_H_ */
