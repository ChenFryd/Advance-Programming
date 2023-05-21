//
// Created by chen on 1/8/23.
//

#include "PoliticianRepublicanSocial.h"

PoliticianRepublicanSocial::PoliticianRepublicanSocial(const std::string &first_name, const std::string &family_name,
                                                       const int &id, const int &power): Politician(first_name,family_name,id,power){}

void PoliticianRepublicanSocial::print_politician()const {
    cout<<"Republican Person:"<<m_politician_name<<" "<<m_politician_family_name<<", Id:"<<m_politician_id<<", Power:"<<m_politician_power<<", Type:S, Chairman: "<<m_director_name_politician_party<<endl;
}

bool PoliticianRepublicanSocial::is_politician_demo()const {
    return false;
}
bool PoliticianRepublicanSocial::is_politician_repub()const {
    return true;
}
bool PoliticianRepublicanSocial::is_politician_leader()const{
    return false;
}
bool PoliticianRepublicanSocial::is_politician_social()const {
    return true;
}


PoliticianRepublicanSocial::~PoliticianRepublicanSocial() {}