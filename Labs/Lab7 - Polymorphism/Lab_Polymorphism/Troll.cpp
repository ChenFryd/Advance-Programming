#include "Troll.h"

std::string Troll::getType()
{
	return "Troll";
}

void Troll::fight(Creature &c)
{
	if (c.getType() == this->getType())
	{
		cout << "2 Trolls met - no fight\n";
		return;
	}

	cout << this->getType() << " fought " << c.getType() << " - ";
	if (c.getType() == "Penguin")
	{
		// Troll won
		cout << this->getType() << " has won\n";
		this->gainHealth(20);
		c.hurtHealth(50);
	}
	else if(c.getType() == "Wolf")
	{
		// Troll lost
		cout << c.getType() << " has won\n";
		this->hurtHealth(50);
		c.gainHealth(20);
	}
}

void Troll::drinkHealth()
{
	cout << "Troll has drank Health\n";
	this->hurtHealth(10);
}

void Troll::drinkPoison()
{
	cout << "Troll has drank Poison\n";
	this->gainHealth(5);
}

void Troll::drinkBeer()
{
	cout << "Troll has drank Beer\n";
	this->gainHealth(5);
}

