//
// Created by chen on 12/19/22.
//

#include "Address.h"
using namespace std;

Address::Address(){
    _city=nullptr;
    _street=nullptr;
    _num = 0;
    std::cout <<"New Address"<<endl;
};

Address::~Address(){
    if (nullptr != _city)
        free(_city);
    if(nullptr != _street)
        free(_street);

    std::cout << "Address deleted"<<endl;
};

void Address::print(){
    cout <<"["<<_city<<", "<<_street<<", "<<_num<<"]";
}

void Address::setAddress(char *city, char *street, int number) {
    _city = (char*)malloc(strlen(city)+1);
    strcpy(_city,city);
    _street = (char*)malloc(strlen(street)+1);
    strcpy(_street,street);
    _num=number;
};