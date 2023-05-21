//
// Created by chen on 12/19/22.
//
#include "Date.h"

Date::Date(){
    _year=1900;
    _month = OCT;
    _day = 1;
    cout<<"New Date" << endl;
};

void Date::setDate(int year,eMonth month,int day)
{
    _year = year;
    _month=month;
    _day=day;
};

void Date::print(){
    char month[4];
    switch (_month) {
        case (OCT):
            strcpy(month,"OCT"); break;
        case(NOV):
            strcpy(month,"NOV"); break;
        default:
            strcpy(month,"NOV"); break;
    }
    cout<<_day<<" of "<<month<<", "<< _year;
};

Date::~Date(){
    cout<<"Date deleted" << endl;
};