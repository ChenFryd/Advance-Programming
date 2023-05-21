//
// Created by chen on 1/9/23.
//

#include "Wolf.h"
std::string Wolf::getType() {
    return "Wolf";
}

void Wolf::fight(Creature &c) {
    if (c.getType() == "Wolf"){
        cout << "2 Wolfs met - no fight" << endl;
        return;
    }
    cout<<"Wolf fought "<<c.getType()<<" - ";
    if (c.getType() == "Penguin"){ //penguin won
        cout<<c.getType()<<" has won"<<endl;
        hurtHealth(50);
        c.gainHealth(20);
    }
    else{ //c is troll. wolf won
        cout<<c.getType()<<" has won"<<endl;
        gainHealth(20);
        c.hurtHealth(50);
    }
}