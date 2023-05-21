//
// Created by chen on 12/19/22.
//

#ifndef LAB4_PERSON_H
#define LAB4_PERSON_H
#include "Date.h"
#include "Address.h"

class Person{
    int _age;
    double _height;
    char *_id;
    Date _birthDate;
    Address _addr;
public:
    Person();
    void setAddress(char* first, char* second, int number);
    void setId(char* id);
    void setDate(int year, eMonth month,int day);
    void print();
    ~Person();

};
#endif //LAB4_PERSON_H
