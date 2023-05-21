//
// Created by chen on 1/10/23.
//

#include "RepublicanParty.h"
RepublicanParty::RepublicanParty(const std::string& m_party_name): Party(m_party_name){}

void RepublicanParty::print_party()const {
    cout<<"Republican Party: "<<m_party_name<<", chairman:"<<get_dir_party_name()<<", Size:"<<m_party_politicians.size()<<endl;
    for (auto it = begin(m_party_politicians);it != end(m_party_politicians);++it) {
        cout<<"\t";
        (*it)->print_politician();
    }
}

bool RepublicanParty::is_party_repub()const {
    return true;
}

bool RepublicanParty::is_party_demo()const {
    return false;
}

RepublicanParty::~RepublicanParty() {}