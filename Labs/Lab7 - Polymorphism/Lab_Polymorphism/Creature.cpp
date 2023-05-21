/*
 * Creature.cpp
 *
 *  Created on: 29 Dec 2021
 *      Author: user
 */

#include "Creature.h"

void Creature::hurtHealth(int amount)
{
	cout << "\t" << this->getType() << " : ";
	this->health_stat -= amount;
	if(this->health_stat < 0)
	{
		this->health_stat = 0;
		cout << "I have died!\n";
	}
	else
	{
		cout << "hurt for " << amount << " points\n";
	}
}

void Creature::gainHealth(int amount)
{
	if(this->health_stat == MAX_HEALTH)
	{
		return;
	}

	this->health_stat += amount;

	if(this->health_stat > MAX_HEALTH)
	{
		this->health_stat = MAX_HEALTH;
	}
	cout << "\t" << this->getType() << " : ";
	cout << "gained " << amount << " points\n";
}
