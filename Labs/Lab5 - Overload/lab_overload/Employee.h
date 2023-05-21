//
// Created by Chen on 31-Dec-22.
//

#ifndef LAB4_EMPLOYEE_H
#define LAB4_EMPLOYEE_H
#include <iostream>
using namespace std;

class Employee {
private:
    static int cound_id;
    char* m_employee_name;
    double m_salary;
public:
    //default constructor
    Employee();

    Employee(char* name,double salary);

    //copy constructor
    Employee(const Employee &cEmployee);

    //operators
    bool operator==(const Employee& employee_other)const;
    bool operator>(const Employee& employee_other)const;
    Employee& operator+(const Employee& employee_other);
    Employee& operator++();
    Employee& operator+=(const Employee& employee_other);
    static int getNumberOfEmployee(){
        return cound_id;
    }
    virtual ~Employee();
    friend ostream& operator<<(ostream& out,const Employee& employee);
};


#endif //LAB4_EMPLOYEE_H
