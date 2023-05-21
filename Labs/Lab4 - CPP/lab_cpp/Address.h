//
// Created by chen on 12/19/22.
//

#ifndef LAB4_ADDRESS_H
#define LAB4_ADDRESS_H
#include <string.h>
#include <iostream>

class Address{
    char* _city;
    char* _street;
    int _num;
public:
    Address();
    ~Address();
    void setAddress(char* city, char* street, int number);
    void print();
};
#endif //LAB4_ADDRESS_H
