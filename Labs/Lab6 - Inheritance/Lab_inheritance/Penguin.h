//
// Created by chen on 1/9/23.
//

#ifndef LAB5_PENGUIN_H
#define LAB5_PENGUIN_H
#include "Creature.h"

class Penguin : public Creature {
public:
    Penguin():Creature(){};
    virtual ~Penguin(){};
    virtual std::string getType();
    virtual void fight(Creature& c);
};


#endif //LAB5_PENGUIN_H
