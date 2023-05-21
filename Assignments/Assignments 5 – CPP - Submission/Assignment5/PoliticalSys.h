//
// Created by chen on 1/8/23.
//

#ifndef ASSIGMENT5_POLITICALSYS_H
#define ASSIGMENT5_POLITICALSYS_H

#include "Error.h"
#include "PoliticianDemocraticLeader.h"
#include "PoliticianDemocraticSocial.h"
#include "PoliticianRepublicanLeader.h"
#include "PoliticianRepublicanSocial.h"

#include "DemocraticParty.h"
#include "RepublicanParty.h"

#include <vector>
#include <iostream>
#include <string>
using namespace std;

class PoliticalSys {
private:
    //vectors to check what kind of the politican is
    std::vector<Politician*> m_vector_politicians;
    std::vector<Party*> m_vector_parties;

    //members to check in o(1). there is a function that updates it.
    int m_size_of_biggest_party;
    std::string m_name_biggest_party;
    void update_biggest_party();

    //in order to move politicans after creating a new one.
    bool move_politician_inside_parties(Politician *const politician_to_move);
    //std::string const check_political_system_by_party_name(const std::string& party_name)const;

    //creating new politican and party
    Politician* create_new_politician(const std::string& first_name,const std::string& last_name,const int& id, const int& power, const std::string& party,const std::string& social_or_leader);
    Party* create_new_party(const std::string& new_party_name_input,const std::string& new_party_type);

    //after creating a new politican, this is the method to move them
    bool move_politician_with_new_party(Party*const new_party,Politician * const politician_to_move);
public:
    PoliticalSys();
    //char* and not string because of argv
    PoliticalSys(char* const file_path);
    void removeParty();
    void addParty();
    void elections();
    void printPoliticians()const;
    void printParties()const;
    void BiggestParty();
    void addPolitician();
    void removePolitician();
    ~PoliticalSys();
};


#endif //ASSIGMENT5_POLITICALSYS_H
