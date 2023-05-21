//
// Created by Chen on 31-Dec-22.
//
#pragma once
#ifndef ASS4_ROBOT_H
#define ASS4_ROBOT_H

// this is the class for robot
// it doesn't know the map he is in. that is the purpose of Game.h

class Robot {
private:
    static int id_counter;
    int _id;
    int _map_number;
    int _positionX;
    int _positionY;
    bool _can_move;
public:
    //constructor. needs map_number, positionX,positionY
    Robot(const int map_number,const int positionX,const int positionY);

    //constructor
    ~Robot(){};

    //get functions. returns a private member of the class
    const int getRobotId()const;
    const int getMapNumber()const;
    const int getLocationX()const;
    const int getLocationY()const;
    const bool canMove()const;

    //setter.
    void setCanMove(const bool bool_input);
    void setLocationX(const int new_location_x);
    void setLocationY(const int new_location_y);
};


#endif //ASS4_ROBOT_H