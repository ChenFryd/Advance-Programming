//
// Created by chen on 1/8/23.
//

#ifndef ASSIGMENT5_POLITICIAN_H
#define ASSIGMENT5_POLITICIAN_H
#include "Party.h"
#include <iostream>
#include <string>
//using namespace std;

class Party;
class Politician{
private:
protected:
    //const member are not to be changed
    std::string const m_politician_name;
    std::string const m_politician_family_name;
    int const m_politician_id;
    //fluid. can be changed if the party changes or dir changes
    Party* m_politician_party;
    std::string m_director_name_politician_party;
    int const m_politician_power;
public:
    Politician(const std::string& name,const std::string& family_name,const int& id,const int& power);
    //chckers
    virtual bool is_politician_demo()const=0;
    virtual bool is_politician_repub()const=0;
    virtual bool is_politician_leader()const=0;
    virtual bool is_politician_social()const=0;
    //return id
    const int& get_id()const;
    //pure virtual. each class inhertince need to implament this
    virtual void print_politician()const=0;
    //sets the politician party
    void set_politician_party(Party* const party_to_set);
    //returns the party that the politican belongs to
    Party* const get_pointer_politician_party()const;
    //removes a politician from the party.
    void remove_politician_from_party();
    //the politican asks his party who is the current director. uses the observor structure.
    void set_dir_politician();
    //returns who is the current dir
    const std::string& get_dir_name()const;
    //returns the power
    const int& get_power()const;
    //returns the name
    const std::string& get_name()const;
    //returns the amount of members in the current party
    int get_amount_of_party_members_in_current_party()const;
    //remove dir from politician
    void remove_dir();
    virtual ~Politician();
};


#endif //ASSIGMENT5_POLITICIAN_H
