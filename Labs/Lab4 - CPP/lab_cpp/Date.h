//
// Created by chen on 12/19/22.
//

#ifndef LAB4_DATE_H
#define LAB4_DATE_H
#include <iostream>
#include <string.h>
using namespace std;

enum eMonth {OCT=10,NOV=11};

class Date {
private:
    int _year;
    eMonth _month;
    int _day;
public:
    Date();
    ~Date();
    void setDate(int year, eMonth month,int day);
    void print();
};


#endif //LAB4_DATE_H
