//
// Created by chen on 1/8/23.
//

#include "Party.h"
#include <algorithm>

Party::Party(const std::string &m_party_name) : m_party_name(m_party_name) {
    this->m_dir_party = nullptr;
}

bool Party::delete_politician(Politician* politician_to_delete) {
    if (politician_to_delete == nullptr)
        return false;
    if (m_dir_party != nullptr) {
        if (politician_to_delete->get_id() == m_dir_party->get_id()) {
            notify_and_remove_dir_party();
        }

    }
    politician_to_delete->remove_dir();
    m_party_politicians.erase(std::remove(m_party_politicians.begin(), m_party_politicians.end(), politician_to_delete));
    return true;
}
void Party::notify_all_politicians_new_dir() const {
    for(auto it_politician = m_party_politicians.begin();it_politician != m_party_politicians.end();++it_politician)
    {
        (*it_politician)->set_dir_politician();
    }
}
void Party::primary_election() {
    int highest_power=-1;
    Politician* highest_power_politician = nullptr;
    for(auto it_politician=m_party_politicians.begin();it_politician!= m_party_politicians.end(); ++it_politician) {
        if ((*it_politician)->is_politician_leader()) {
            int curr_politician_power = (*it_politician)->get_power();
            if (curr_politician_power > highest_power) {
                highest_power_politician = *it_politician;
                highest_power = curr_politician_power;
            }
        }
    }
    if (highest_power_politician == nullptr)
        return;
    else
        this->m_dir_party=highest_power_politician;

    notify_all_politicians_new_dir();
    cout<<this->m_dir_party->get_name()<<" is the chairman of "<<this->m_party_name<<endl;


}

int const Party::calculate_strength() const {
    int power_overall=0;
    for(auto it_politician=m_party_politicians.begin(); it_politician != m_party_politicians.end(); ++it_politician){
        if ((*it_politician)->is_politician_social())
            power_overall += 2*(*it_politician)->get_power();
        else if ((*it_politician)->is_politician_leader())
            power_overall += (*it_politician)->get_power();
        else
            throw InvalidData();
    }
    cout<<"Party: "<<this->m_party_name<<",Power: "<<power_overall<<endl;
    return power_overall;
}

bool Party::add_politician(Politician* const politician_to_add) {
    if (politician_to_add == nullptr)
        return false;
    Party* p_politician_party =(*politician_to_add).get_pointer_politician_party();
    if ( p_politician_party != nullptr){
        (*p_politician_party).delete_politician(politician_to_add);
    }
    politician_to_add->set_politician_party(this);
    politician_to_add->set_dir_politician();
    this->m_party_politicians.push_back(politician_to_add);
    return true;
}


const string Party::get_party_name()const {
    return this->m_party_name;
}

int const Party::get_amount_of_politicians()const {
    return (this->m_party_politicians).size();
}

vector<Politician *> Party::get_politicians() const {
    return this->m_party_politicians;
}

const std::string Party::get_dir_party_name()const{
    if (this->m_dir_party == nullptr)
        return "None";
    return this->m_dir_party->get_name();
}

void Party::notify_and_remove_dir_party() {
    m_dir_party = nullptr;
    notify_all_politicians_new_dir();
}
Party::~Party() {
    notify_and_remove_dir_party();
    for (auto it_politician=m_party_politicians.begin(); it_politician != m_party_politicians.end();++it_politician){
        (*it_politician)->set_politician_party(nullptr);
    }
    m_party_politicians.clear();
}