//
// Created by chen on 1/8/23.
//

#include "PoliticianRepublicanLeader.h"
PoliticianRepublicanLeader::PoliticianRepublicanLeader(const std::string &first_name, const std::string &family_name,
                                                       const int &id, const int &power) : Politician(first_name,family_name,id,power) {}

void PoliticianRepublicanLeader::print_politician()const {
    cout<<"Republican Person:"<<m_politician_name<<" "<<m_politician_family_name<<", Id:"<<m_politician_id<<", Power:"<<m_politician_power<<", Type:L, Chairman: "<<get_dir_name()<<endl;
}

bool PoliticianRepublicanLeader::is_politician_demo()const {
    return false;
}
bool PoliticianRepublicanLeader::is_politician_repub()const {
    return true;
}
bool PoliticianRepublicanLeader::is_politician_leader()const{
    return true;
}
bool PoliticianRepublicanLeader::is_politician_social()const {
    return false;
}


PoliticianRepublicanLeader::~PoliticianRepublicanLeader() {}