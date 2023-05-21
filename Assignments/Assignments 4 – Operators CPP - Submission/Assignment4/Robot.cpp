//
// Created by Chen on 31-Dec-22.
//

#include "Robot.h"
#include <iostream>
using namespace std;
int Robot::id_counter=0;

Robot::Robot(int map_number, int positionX, int positionY) {
    id_counter++;
    this->_id = id_counter;
    this->_map_number = map_number;
    this->_positionX = positionX;
    this->_positionY = positionY;
    this->_can_move = true;
    cout<<"New Robot: "<<this->_id<<" MAP: "<<map_number<<" GPS: "<<positionX<<","<<positionY<<endl;
}

const int Robot::getMapNumber() const {
    return this->_map_number;
}

const int Robot::getRobotId() const {
    return this->_id;
}

const int Robot::getLocationX() const {
    return this->_positionX;
}

const int Robot::getLocationY() const {
    return this->_positionY;
}

const bool Robot::canMove() const {
    return this->_can_move;
}

void Robot::setCanMove(const bool bool_to_change_can_move){
    this->_can_move= bool_to_change_can_move;
    this->_positionX=-1;
    this->_positionY=-1;
}

void Robot::setLocationX(const int new_int_location_x) {
    this->_positionX=new_int_location_x;
}

void Robot::setLocationY(const int new_int_location_y) {
    this->_positionY=new_int_location_y;
}
