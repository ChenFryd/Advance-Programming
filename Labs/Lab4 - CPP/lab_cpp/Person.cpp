//
// Created by chen on 12/19/22.
//
#include "Person.h"
using namespace std;
Person::Person(){
    _age=0;
    _height=0;
    _id=nullptr;
    cout<<"New Person"<<endl;
};

void Person::setAddress(char *first, char *second, int number) {
    _addr.setAddress(first,second,number);
}

void Person::setDate(int year, eMonth month, int day) {
    _birthDate.setDate(year,month,day);
}

void Person::setId(char *id) {
    _id=(char*)malloc(strlen(id)+1);
    if(_id == nullptr)
        _id= nullptr;
    strcpy(_id,id);
}

void Person::print() {
    cout<<"PERSON, id="<<_id<<", age ="<<_age<<", height="<<_height<<"."<<endl;
    cout<<"Born on ";
    _birthDate.print();
    cout<<"\nLives in ";
    _addr.print();
}

Person::~Person(){
    if (nullptr != _id)
        free(_id);
    cout<<"Person deleted"<<endl;
}