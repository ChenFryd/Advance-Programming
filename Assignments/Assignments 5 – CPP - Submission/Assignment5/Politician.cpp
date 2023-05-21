//
// Created by chen on 1/8/23.
//

#include "Politician.h"
Politician::Politician(const std::string &name, const std::string &family_name, const int &id, const int &power)
    :m_politician_name(name),m_politician_family_name(family_name),m_politician_id(id),m_politician_power(power) {
    this->m_politician_party= nullptr;
    this->m_director_name_politician_party = "None";
}

const int& Politician::get_id() const {
    return this->m_politician_id;
}

void Politician::set_politician_party(Party* const party_to_set){
    this->m_politician_party=party_to_set;
}

Party* const Politician::get_pointer_politician_party() const {
    return this->m_politician_party;
}

int Politician::get_amount_of_party_members_in_current_party() const {
    if (this->m_politician_party == nullptr)
        return 1000000; //ideal it would be inf, but excesive for this hw
    return (*(this->m_politician_party)).get_amount_of_politicians();
}

void Politician::set_dir_politician() {
    if (m_politician_party != nullptr)
        this->m_director_name_politician_party = (m_politician_party)->get_dir_party_name();
    else
        this->m_director_name_politician_party = "None";
}

const int& Politician::get_power() const {
    return this->m_politician_power;
}
const std::string& Politician::get_name()const {

    return this->m_politician_name;
}

const std::string& Politician::get_dir_name() const {
    return this->m_director_name_politician_party;
}
void Politician::remove_politician_from_party() {
    m_politician_party->delete_politician(this);
    m_politician_party=nullptr;
}
void Politician::remove_dir() {
    m_director_name_politician_party="None";
}
Politician::~Politician() {
    if (m_politician_party != nullptr)
        m_politician_party->delete_politician(this);
}