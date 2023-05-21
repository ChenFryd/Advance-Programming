//
// Created by chen on 1/8/23.
//

#ifndef ASSIGMENT5_PARTY_H
#define ASSIGMENT5_PARTY_H
#include "Politician.h"
#include "Error.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Politician;

class Party{
protected:
    const std::string m_party_name;
    Politician* m_dir_party;
    std::vector<Politician*> m_party_politicians;
public:
    Party(const std::string& m_party_name);
    //checks what kind of the party
    virtual bool is_party_demo()const=0;
    virtual bool is_party_repub()const=0;
    //add politician to the party
    bool add_politician(Politician* const politician_to_add);
    //removes a politican.
    bool delete_politician(Politician* const politician_to_delete);
    //selects a party director.
    void primary_election();
    //calculate strength with a regard to the type of the politician
    int const calculate_strength()const;
    //pure virtual. each class inhertince implaments it.
    virtual void print_party()const=0;
    const string get_party_name()const;
    int const get_amount_of_politicians()const;
    //uses the observer structure
    void notify_all_politicians_new_dir()const;
    //returns the vector of politicians in order to move them
    vector<Politician*> get_politicians()const;
    //return the name of the dir party. uses the observer structure.
    const std::string get_dir_party_name()const;
    //removes the dir from all the politicians
    void notify_and_remove_dir_party();
    virtual ~Party();
};


#endif //ASSIGMENT5_PARTY_H
