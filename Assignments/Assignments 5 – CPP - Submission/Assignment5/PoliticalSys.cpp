//
// Created by chen on 1/8/23.
//

#include "PoliticalSys.h"
#include <algorithm>
#include <fstream>

//cant be used in the constructor since this doesn't know the size and the name yet.
void PoliticalSys::update_biggest_party() {
    m_name_biggest_party = "None";
    m_size_of_biggest_party =-1;
    for(auto it_party=m_vector_parties.begin();it_party != m_vector_parties.end(); ++it_party){
        int curr_party_size =(*it_party)->get_amount_of_politicians();
        std::string curr_party_name = (*it_party)->get_party_name();
        if ( curr_party_size > this->m_size_of_biggest_party){
            this->m_name_biggest_party = (*it_party)->get_party_name();
            this->m_size_of_biggest_party =curr_party_size;
        }
        else if ( curr_party_size == this->m_size_of_biggest_party){
            if (curr_party_name > this->m_name_biggest_party){
                this->m_name_biggest_party = curr_party_name;
                this->m_size_of_biggest_party =curr_party_size;
            }
        }
    }
}
//just creates the politician. doesn't assign him to a new party
Politician* PoliticalSys::create_new_politician(const std::string &first_name, const std::string &last_name,
                                                const int &id, const int &power, const std::string &party,
                                                const std::string &social_or_leader) {
    Politician* pPolitician;
    if (party == "D") {
        if (social_or_leader == "L") {
            PoliticianDemocraticLeader *new_politician = new PoliticianDemocraticLeader(first_name,last_name,id,power);
            pPolitician = new_politician;
        } else {
            PoliticianDemocraticSocial *new_politician = new PoliticianDemocraticSocial(first_name,last_name,id,power);
            pPolitician = new_politician;
        }
    }
    else {
        if (party == "R") {
            if (social_or_leader == "L") {
                PoliticianRepublicanLeader *new_politician = new PoliticianRepublicanLeader(first_name,last_name,id,power);
                pPolitician = new_politician;
            } else {
                PoliticianRepublicanSocial *new_politician = new PoliticianRepublicanSocial(first_name,last_name,id,power);
                pPolitician = new_politician;
            }
        }
    }
    m_vector_politicians.push_back(pPolitician);
    return pPolitician;
}

//moves the politican inside the parties.
bool PoliticalSys::move_politician_inside_parties(Politician *const politician_to_move) {
    bool found_party=false;
    for(auto it_party = m_vector_parties.begin();it_party != m_vector_parties.end(); ++it_party) {
        //if the party and the politician are the same
        if (((*it_party)->is_party_demo() && politician_to_move->is_politician_demo()) || ((*it_party)->is_party_repub() && politician_to_move->is_politician_repub())) {
            {
                string curr_demo_party_name = (*it_party)->get_party_name();
                if (politician_to_move->get_amount_of_party_members_in_current_party() >
                    (*it_party)->get_amount_of_politicians()) {
                    (*it_party)->add_politician(politician_to_move);
                    found_party = true;
                }
            }
        }
    }
    return found_party;
}

//moves the politician when there is a new party. it isn't the same to the function above.
bool PoliticalSys::move_politician_with_new_party(Party *const new_party, Politician *const politician_to_move) {
    bool found_party=false;
    string curr_party_name = new_party->get_party_name();
    if ((new_party->is_party_demo()&&politician_to_move->is_politician_demo())||(new_party->is_party_repub() &&politician_to_move-> is_politician_repub()) ) {
            //after that we find the party with the lowest party memebers
        if (politician_to_move->get_amount_of_party_members_in_current_party() >
            new_party->get_amount_of_politicians()) {
            new_party->add_politician(politician_to_move);
            found_party = true;
        }
    }
    return found_party;

}

//creates a new party. doesn't move any politicians into.
Party* PoliticalSys::create_new_party(const std::string &new_party_name_input, const std::string& new_party_type) {
    Party *party_output;
    if (new_party_type == "D") {
        DemocraticParty *new_demo_party = new DemocraticParty(new_party_name_input);
        party_output = new_demo_party;
    } else if (new_party_type == "R") {
        RepublicanParty *new_repub_party = new RepublicanParty(new_party_name_input);
        party_output = new_repub_party;
    } else {
        throw InvalidData();
    }
    m_vector_parties.push_back(party_output);
    return party_output;
}

PoliticalSys::PoliticalSys(char* const file_path){
    std::ifstream file_input(file_path);
    std::string myline;
    string first_name_file;
    string last_name_file;
    int id_file;
    int power_file;
    string type_party_file;
    string leader_or_social_file;
    string party_name_file;
    bool line_politicians = false;
    bool line_parties = false;
    if (file_input.is_open()){
        while(std::getline(file_input, myline)){
            if (!myline.empty() && myline[myline.size() - 1] == '\r')
                myline.erase(myline.size() - 1);
            if (myline == "Politicians:"){
                line_politicians = true;
                continue;
            }
            if (myline == "Parties:") {
                line_politicians=false;
                line_parties=true;
                continue;
            }
            if (line_politicians){
                first_name_file = myline.substr(0, myline.find(" "));
                myline = myline.substr(myline.find(" ")+1);
                last_name_file = myline.substr(0, myline.find(" "));
                myline = myline.substr(myline.find(" ")+1);
                id_file = stoi(myline.substr(0,myline.find(" ")));
                myline = myline.substr(myline.find(" ")+1);
                power_file = stoi(myline.substr(0,myline.find(" ")));
                myline = myline.substr(myline.find(" ")+1);
                type_party_file = myline.substr(0,myline.find(" "));
                myline = myline.substr(myline.find(" ")+1);
                leader_or_social_file = myline.substr(0,myline.find(" "));
                create_new_politician(first_name_file,last_name_file,id_file,power_file,type_party_file,leader_or_social_file);
                continue;
            }
            if (line_parties){
                party_name_file = myline.substr(0,myline.find(" "));
                myline = myline.substr(myline.find(" ")+1);
                type_party_file = myline;
                myline = myline.substr(myline.find(" ")+1);
                Party* new_party = create_new_party(party_name_file,type_party_file);

                for(auto it_politician=m_vector_politicians.begin();it_politician!=m_vector_politicians.end();++it_politician){
                        move_politician_with_new_party(new_party,*it_politician);
                }
            }
        }
    }
    file_input.close();
    update_biggest_party();
}

//default constructor.
PoliticalSys::PoliticalSys() {
    this->m_vector_parties;
    this->m_vector_politicians;
    update_biggest_party();
}

void PoliticalSys::addPolitician(){
    cout<<"---Create Politician---"<<endl;
    bool legal_param= false;
    std::string new_politician_first_name;
    std::string new_politician_last_name;
    int new_politician_id;
    int new_politician_power;
    std::string new_politician_leader_or_social;
    std::string new_politician_party;
    while(legal_param == false){
        legal_param = true;
        cout<<"First name:"<<endl;
        cin>>new_politician_first_name;
        cout<<"Last name:"<<endl;
        cin>>new_politician_last_name;
        cout<<"ID:"<<endl;
        cin>>new_politician_id;
        //CHECK ID IF POSITIVE NUMBER
        if (new_politician_id <1) {
            legal_param = false;
        }
        //CHECK ID IF EXIST
        for (auto it = m_vector_politicians.begin(); it != m_vector_politicians.end(); ++it) {
            if ((*it)->get_id() == new_politician_id) {
                legal_param = false;
                break;
            }
        }
        cout<<"Power:"<<endl;
        cin>>new_politician_power;
        //CHECK IF POWER IS NOT BELOW ZERO
        if (new_politician_power <0) {
            legal_param= false;
        }

        cout<<"Republican or Democratic person"<<endl;
        cin>>new_politician_party;
        //CHECK IF THE PARTY IS R OR D
        if (new_politician_party != "D" && new_politician_party != "R") {
            legal_param= false;
        }

        cout<<"Leader or Social"<<endl;
        cin>>new_politician_leader_or_social;
        //CHECK IF HE IS L OR S
        if(new_politician_leader_or_social != "L" && new_politician_leader_or_social != "S")
            legal_param= false;

        try {
            if (legal_param == false)
                throw InvalidData();
        }
        catch(Error& error)
        {
            error.handle();
        }
    }
    Politician* pPolitician = create_new_politician(new_politician_first_name,new_politician_last_name,new_politician_id,new_politician_power,new_politician_party,new_politician_leader_or_social);
    move_politician_inside_parties(pPolitician);
    pPolitician->set_dir_politician();
    update_biggest_party();
}

void PoliticalSys::addParty(){
    cout<<"---Create Party---"<<endl;
    string new_party_name;
    string new_type_of_party;
    bool found_legit_name = false;
    while(found_legit_name == false) {
        cout<<"Name:"<<endl;
        cin>>new_party_name;
        found_legit_name = true;
        try {
            for (auto it = m_vector_parties.begin(); it != m_vector_parties.end(); ++it) {
                if ((*it)->get_party_name() == new_party_name) {
                    throw NameError();
                }
            }
            cout << "Republican or Democratic party" << endl;
            cin >> new_type_of_party;
            if (new_type_of_party != "D" && new_type_of_party != "R") {
                throw InvalidData();
            }
        }
        catch (Error &error) {
            found_legit_name = false;
            error.handle();
        }
    }
    Party* new_party = create_new_party(new_party_name,new_type_of_party);
    for(auto it_politician=m_vector_politicians.begin();it_politician!=m_vector_politicians.end();++it_politician){
            move_politician_with_new_party(new_party,(*it_politician));
    }
    update_biggest_party();
}

void PoliticalSys::removeParty() {
    if (m_vector_parties.size() == 0)
        return;
    cout << "---Remove Party---" << endl;
    string party_name_to_delete;
    Party *party_to_delete;
    bool found_party = false;
    while (found_party != true) {
        cout << "Enter party name:" << endl;
        cin >> party_name_to_delete;
        for (auto it_party = m_vector_parties.begin(); it_party != m_vector_parties.end(); ++it_party) {
            string curr_party_name = (*it_party)->get_party_name();
            if (party_name_to_delete == curr_party_name) {
                party_to_delete = (*it_party);
                found_party = true;
                break;
            }
        }
        try {
            if (found_party == false)
                throw NameError();
        }
        catch(Error& error){
            error.handle();
        }
    }
    //delete the dir from all the politicians
    party_to_delete->notify_and_remove_dir_party();
    //PoliticalSys is responsible to move the politician so that's why we get the vector
    vector<Politician *> vector_politicians_from_the_removed_party = party_to_delete->get_politicians();
    //this line is important. that's how to system know not to check the same party.
    m_vector_parties.erase(std::remove(m_vector_parties.begin(), m_vector_parties.end(), party_to_delete));
    for (auto it_politician = vector_politicians_from_the_removed_party.begin();
        it_politician != vector_politicians_from_the_removed_party.end(); ++it_politician) {
        (*it_politician)->remove_politician_from_party();
        move_politician_inside_parties((*it_politician));
    }
    delete party_to_delete;

    update_biggest_party();
}




void PoliticalSys::elections(){
    if (m_vector_parties.size() == 0 || m_vector_politicians.size() == 0)
        return;
    cout<<"----Primaries----"<<endl;
    for(auto it_party=m_vector_parties.begin(); it_party != m_vector_parties.end(); ++it_party){
        (*it_party)->primary_election();
    }
    cout<<"----Elections----"<<endl;
    int highest_overall_power=-1;
    Party* highest_party_with_overall_power;
    int curr_party_overall_power;
    for(auto it_party=m_vector_parties.begin(); it_party != m_vector_parties.end(); ++it_party){
        curr_party_overall_power = (*it_party)->calculate_strength();
        if (curr_party_overall_power > highest_overall_power){
            highest_party_with_overall_power = (*it_party);
            highest_overall_power = curr_party_overall_power;
        }
    }
    cout<<"----Elections Results----"<<endl;
    cout<<highest_party_with_overall_power->get_party_name()<<" party won the elections and "<<highest_party_with_overall_power->get_dir_party_name()<<" is the prime minister"<<endl;
}
void PoliticalSys::printPoliticians()const{
    if (m_vector_politicians.size() == 0)
        return;
    cout<<"----Politicians----"<<endl;
    for (auto it_politician = m_vector_politicians.begin(); it_politician != m_vector_politicians.end(); ++it_politician){
        (*it_politician)->print_politician();
    }
}
void PoliticalSys::printParties()const{
    if (m_vector_parties.size() == 0 )
        return;
    cout<<"----Parties----"<<endl;
    for (auto it_party = m_vector_parties.begin(); it_party != m_vector_parties.end();++it_party){
        (*it_party)->print_party();
    }
}
void PoliticalSys::BiggestParty(){
    if (m_size_of_biggest_party == -1)
        return;
    cout<<"----Biggest Party----"<<endl;
    cout << "[" << this->m_name_biggest_party << "," << this->m_size_of_biggest_party << "]" << endl;
}

void PoliticalSys::removePolitician(){
    if (m_vector_politicians.size() ==0)
        return;
    cout<<"---Remove Politician---"<<endl;
    bool legal_param = false;
    int id_politician_to_delete;
    Politician* politician_to_delete;
    if (m_vector_politicians.size() == 0)
        return;
    while(legal_param == false) {
        cout << "Enter the ID: " << endl;
        cin >> id_politician_to_delete;
        for (auto it = m_vector_politicians.begin(); it != m_vector_politicians.end(); ++it) {
            if ((*it)->get_id() == id_politician_to_delete) {
                politician_to_delete = (*it);
                legal_param = true;
                break;
            }
        }
        try {
            if (legal_param == false)
                throw IdError();
        }
        catch (Error& error){
            error.handle();
        }
    }
    m_vector_politicians.erase(std::remove(m_vector_politicians.begin(), m_vector_politicians.end(), politician_to_delete));
    delete politician_to_delete;
    update_biggest_party();
}


PoliticalSys::~PoliticalSys(){
    //the politician is responsible to delete itself and not the parties.
    for(auto it_politican=m_vector_politicians.begin(); it_politican!=m_vector_politicians.end();++it_politican){
        delete (*it_politican);
    }
    m_vector_politicians.clear();
    for(auto it_party=m_vector_parties.begin();it_party!=m_vector_parties.end();++it_party)
    {
        delete (*it_party);
    }
    m_vector_parties.clear();
}