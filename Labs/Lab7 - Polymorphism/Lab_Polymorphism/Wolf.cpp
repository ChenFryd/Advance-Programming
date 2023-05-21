#include "Wolf.h"


std::string Wolf::getType()
{
	return "Wolf";
}

void Wolf::fight(Creature &c)
{
	if (c.getType() == this->getType())
	{
		cout << "2 Wolves met - no fight\n";
		return;
	}

	cout << this->getType() << " fought " << c.getType() << " - ";
	if (c.getType() == "Troll")
	{
		// Wolf won
		cout << this->getType() << " has won\n";
		this->gainHealth(20);
		c.hurtHealth(50);
	}
	else if(c.getType() == "Penguin")
	{
		// Wolf lost
		cout << c.getType() << " has won\n";
		this->hurtHealth(50);
		c.gainHealth(20);
	}
}

void Wolf::drinkHealth()
{
	cout << "Wolf has drank Health\n";
	this->gainHealth(10);
}

void Wolf::drinkPoison()
{
	cout << "Wolf has drank Poison\n";
	this->hurtHealth(5);
}

void Wolf::drinkBeer()
{
	cout << "Wolf has drank Beer\n";
	this->hurtHealth(5);
}
