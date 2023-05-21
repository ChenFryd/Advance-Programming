//
// Created by chen on 1/8/23.
//

#ifndef ASSIGMENT5_POLITICIANDEMOCRATICLEADER_H
#define ASSIGMENT5_POLITICIANDEMOCRATICLEADER_H
#include "Politician.h"

class PoliticianDemocraticLeader : public Politician{
public:
    //constructor
    PoliticianDemocraticLeader(const std::string& first_name,const std::string& family_name,const int& id,const int& power);
    //print
    virtual void print_politician()const;
    //checks by polymorphism if the politician has some attributes.
    virtual bool is_politician_demo()const;
    virtual bool is_politician_repub()const;
    virtual bool is_politician_leader()const;
    virtual bool is_politician_social()const;
    //destructor
    virtual ~PoliticianDemocraticLeader();
};


#endif //ASSIGMENT5_POLITICIANDEMOCRATICLEADER_H
