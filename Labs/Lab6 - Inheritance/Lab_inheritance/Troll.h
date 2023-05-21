//
// Created by chen on 1/9/23.
//

#ifndef LAB5_TROLL_H
#define LAB5_TROLL_H

#include "Creature.h"
class Troll: public Creature{
public:
    Troll():Creature(){};
    virtual ~Troll(){};
    virtual std::string getType();
    virtual void fight(Creature& c);
};


#endif //LAB5_TROLL_H
