//
// Created by chen on 1/9/23.
//

#ifndef LAB5_CREATURE_H
#define LAB5_CREATURE_H
#include <string>
#include <iostream>
using namespace std;

class Creature{
private:
    static int MAX_HEALTH;
protected:
    int health_stat;
public:
    Creature():health_stat(MAX_HEALTH){};
    virtual std::string getType()=0;
    virtual void fight(Creature &c)=0;
    void hurtHealth(int amount);
    void gainHealth(int amount);
    virtual ~Creature(){};

};
#endif //LAB5_CREATURE_H
