//
// Created by chen on 1/9/23.
//

#include "Troll.h"
std::string Troll::getType() {
    return "Troll";
}

void Troll::fight(Creature &c) {
    if (c.getType() == getType()) {
        cout << "2 Trolls met - no fight" << endl;
        return;
    }
    cout<<"Troll fought "<<c.getType()<<" - ";
    if (c.getType() == "Penguin"){ //Troll won
        cout<<c.getType()<<" has won"<<endl;
        c.hurtHealth(50);
        gainHealth(20);
    }
    else{ //wolf won
        cout<<c.getType()<<" has won"<<endl;
        c.gainHealth(20);
        hurtHealth(50);
    }

}