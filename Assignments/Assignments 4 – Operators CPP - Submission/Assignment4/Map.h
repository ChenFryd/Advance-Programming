//
// Created by Chen on 31-Dec-22.
//
#pragma once
#ifndef ASS4_MAP_H
#define ASS4_MAP_H
#include <iostream>
using namespace std;

//this module is to create the map class.
//put it mind it doesn't contain the robots, only the game does.
class Map {
private:
    //a matrix to contain the values of wall or not. can be 1 or 0
    int _map_table[7][7];
public:
    //constructors. basic for addition and a normal constructor
    Map(){};
    Map(int map_number);

    //deconstructor
    ~Map(){};

    //get location from y,x coordinates. returns the value from _map_table
    const int getLocation(const int positionY,const int positionX)const;

    //set a new value to _map table. gets 3 ints and doesn't return anything-void.
    void setMapCordinates(const int x,const int y,const int value);

    //operators
    Map operator+(const Map& map_other)const;
    Map& operator+=(const Map& map_other);
    Map& operator=(const Map& map_other);
    const bool operator==(const Map& map_other);
    friend ostream& operator<<(ostream& out,const Map& map);
};


#endif //ASS4_MAP_H