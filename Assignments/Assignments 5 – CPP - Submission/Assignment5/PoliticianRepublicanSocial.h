//
// Created by chen on 1/8/23.
//

#ifndef ASSIGMENT5_POLITICIANREPUBLICANSOCIAL_H
#define ASSIGMENT5_POLITICIANREPUBLICANSOCIAL_H
#include "Politician.h"

class PoliticianRepublicanSocial :public Politician{
public:
    //constuctor
    PoliticianRepublicanSocial(const std::string& first_name,const std::string& family_name,const int& id,const int& power);
    //print
    virtual void print_politician()const;
    //checks by polymorphism if the politician has some attributes.
    virtual bool is_politician_demo()const;
    virtual bool is_politician_repub()const;
    virtual bool is_politician_leader()const;
    virtual bool is_politician_social()const;
    //destuctor
    virtual ~PoliticianRepublicanSocial();
};


#endif //ASSIGMENT5_POLITICIANREPUBLICANSOCIAL_H
