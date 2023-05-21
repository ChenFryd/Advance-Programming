//
// Created by chen on 1/9/23.
//

#include "Creature.h"
int Creature::MAX_HEALTH = 100;

void Creature::gainHealth(int amount) {
    if (this->health_stat == MAX_HEALTH)
        return;
    this->health_stat += amount;
    if (this->health_stat > MAX_HEALTH)
        this->health_stat = MAX_HEALTH;
    cout<<"\t"<<this->getType()<<":";
    cout<<"gained "<<amount<<" points"<<endl;
}

void Creature::hurtHealth(int amount) {
    cout<<"\t"<<getType()<<":";
    this->health_stat -= amount;
    if (this->health_stat<0) {
        this->health_stat = 0;
        cout<<"I have died!"<<endl;
    }
    else
        cout<<"hurt for "<<amount<<" points"<<endl;
}