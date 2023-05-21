//
// Created by chen on 1/9/23.
//

#ifndef LAB5_WOLF_H
#define LAB5_WOLF_H
#include "Creature.h"

class Wolf : public Creature{
public:
    Wolf():Creature(){};
    virtual ~Wolf(){};
    virtual std::string getType();
    virtual void fight(Creature& c);
};

#endif //LAB5_WOLF_H
