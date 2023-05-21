//
// Created by chen on 1/10/23.
//

#ifndef ASSIGMENT5_REPUBLICANPARTY_H
#define ASSIGMENT5_REPUBLICANPARTY_H
#include "Party.h"

class RepublicanParty:public Party {
public:
    //constuctor
    RepublicanParty(const std::string& m_party_name);
    //print
    virtual void print_party()const;
    //checks by polymorphism if the politician has some attributes.
    virtual bool is_party_repub()const;
    virtual bool is_party_demo()const;
    //destructor
    virtual ~RepublicanParty();
};


#endif //ASSIGMENT5_REPUBLICANPARTY_H
