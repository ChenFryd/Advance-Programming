//
// Created by Chen on 31-Dec-22.
//
#include <iostream>
#include <string.h>
#include "Employee.h"
using namespace std;
int Employee::cound_id = 0;
Employee::Employee(){
    this->m_employee_name=new char[1];
    if (this->m_employee_name == NULL)
        return;
    strcpy(this->m_employee_name,"");
    this->m_salary=0;
}
Employee::Employee(char *name, double salary) {
    this->m_employee_name = new char[strlen(name)+1];
    if (this->m_employee_name == NULL)
        return;
    strcpy(this->m_employee_name,name);
    this->m_salary=salary;
    cound_id++;
}
bool Employee::operator==(const Employee& employee_other)const{
    return !strcmp(this->m_employee_name,employee_other.m_employee_name);
}

bool Employee::operator>(const Employee &employee_other) const {
    return this->m_salary>employee_other.m_salary;
}

Employee& Employee::operator+(const Employee &employee_other) {
    this->m_salary += employee_other.m_salary;
    return *this;
}

Employee& Employee::operator++(){
    this->m_salary+= 100;
    return *this;
};

Employee& Employee::operator+=(const Employee &employee_other) {
    char* new_name = new char[strlen(this->m_employee_name) + strlen(employee_other.m_employee_name) + 1];
    strcpy(new_name,this->m_employee_name);
    strcat(new_name,employee_other.m_employee_name);
    delete this->m_employee_name;
    this->m_employee_name= new_name;
    return *this;
}

Employee::~Employee() {
    delete this->m_employee_name;
}
ostream& operator<<(ostream& out,const Employee& employee){
    out << "Name:" <<employee.m_employee_name<<endl;
    out<< "Salary:"<<employee.m_salary<<endl;
    return out;
}

