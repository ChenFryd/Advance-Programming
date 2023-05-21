//
// Created by chen on 1/10/23.
//

#include "DemocraticParty.h"

DemocraticParty::DemocraticParty(const std::string& m_party_name): Party(m_party_name){}


void DemocraticParty::print_party()const {
    cout<<"Democrat Party: "<<m_party_name<<", chairman:"<<get_dir_party_name()<<", Size:"<<m_party_politicians.size()<<endl;
    for (auto it = begin(m_party_politicians);it != end(m_party_politicians);++it) {
        cout<<"\t";
        (*it)->print_politician();
    }
}

bool DemocraticParty::is_party_demo()const {
    return true;
}
bool DemocraticParty::is_party_repub()const {
    return false;
}

DemocraticParty::~DemocraticParty() {}