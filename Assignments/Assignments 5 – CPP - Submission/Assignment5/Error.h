//
// Created by chen on 1/12/23.
//

#ifndef ASSIGMENT5_ERROR_H
#define ASSIGMENT5_ERROR_H

#include <string>
#include <iostream>
//Meir said it ok to put of all those errors in the same file
class Error{
public:
    //pure virtual
    Error(){};
    void virtual handle()=0;
};

class IdError : public Error{
public:
    IdError(){};
    void virtual handle(){std::cout<<"Please enter valid id"<<std::endl;};
};

class NameError : public Error{
public:
    NameError(){};
    void virtual handle(){std::cout<<"Please enter valid name"<<std::endl;};
};
class InvalidData : public Error{
public:
    InvalidData(){};
    void virtual handle(){std::cout<<"Please enter valid details"<<std::endl;};
};
#endif //ASSIGMENT5_ERROR_H
