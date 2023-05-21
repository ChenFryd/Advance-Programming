/*
 * Beer.h
 *
 *  Created on: 5 Jan 2022
 *      Author: user
 */

#ifndef BEER_H_
#define BEER_H_

#include "Potion.h"

class Beer: public Potion {
public:
	Beer(): Potion(){};
	virtual ~Beer(){};
	virtual void drink(Creature &c);
};

#endif /* BEER_H_ */
