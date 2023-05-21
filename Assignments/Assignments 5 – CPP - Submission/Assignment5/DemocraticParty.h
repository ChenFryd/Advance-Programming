//
// Created by chen on 1/10/23.
//

#ifndef ASSIGMENT5_DEMOCRATICPARTY_H
#define ASSIGMENT5_DEMOCRATICPARTY_H
#include "Party.h"

class DemocraticParty:public Party {
public:
    //constructor
    DemocraticParty(const std::string& m_party_name);
    //print
    virtual void print_party()const;
    //checkers
    virtual bool is_party_repub()const;
    virtual bool is_party_demo()const;

    //destuctor
    virtual ~DemocraticParty();
};


#endif //ASSIGMENT5_DEMOCRATICPARTY_H
