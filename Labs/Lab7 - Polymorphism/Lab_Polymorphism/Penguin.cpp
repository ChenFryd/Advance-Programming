#include "Penguin.h"

std::string Penguin::getType()
{
	return "Penguin";
}

void Penguin::fight(Creature &c)
{
	if (c.getType() == this->getType())
	{
		cout << "2 Penguins met - no fight\n";
		return;
	}

	cout << this->getType() << " fought " << c.getType() << " - ";
	if (c.getType() == "Wolf")
	{
		// Penguin won
		cout << this->getType() << " has won\n";
		this->gainHealth(20);
		c.hurtHealth(50);
	}
	else if(c.getType() == "Troll")
	{
		// Penguin lost
		cout << c.getType() << " has won\n";
		this->hurtHealth(50);
		c.gainHealth(20);
	}
}

void Penguin::drinkHealth()
{
	cout << "Penguin has drank Health\n";
	this->gainHealth(5);

}

void Penguin::drinkPoison()
{
	cout << "Penguin has drank Poison\n";
	this->hurtHealth(10);
}

void Penguin::drinkBeer()
{
	cout << "Penguin has drank Beer\n";
	this->gainHealth(5);
}

