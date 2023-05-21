//
// Created by chen on 1/9/23.
//

#include "Penguin.h"
std::string Penguin::getType() {
    return "Penguin";
}

void Penguin::fight(Creature &c) {
    if (c.getType() == getType()) {
        cout << "2 Penguins met - no fight" << endl;
        return;
    }
    cout<<"Penguin fought "<<c.getType()<<" - ";
    if (c.getType() == "Troll"){ //Pinguin lost against Troll
        cout<<c.getType()<<" has won"<<endl;
        this->hurtHealth(50);
        c.gainHealth(20);
    }
    else{ //pinguin won against Wolf
        cout<<getType()<<" has won"<<endl;
        this->gainHealth(20);
        c.hurtHealth(50);
    }

}