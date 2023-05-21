//
// Created by Chen on 01-Jan-23.
//
#pragma once
#ifndef ASS4_GAME_H
#define ASS4_GAME_H
#include "Robot.h"
#include "Map.h"
#include <vector>

//this the class to control the maps and the robots.
//the robots and the maps don't know each other.

class Game{
private:
    //dynamic array of robots pointers.
    vector<Robot*> _array_of_robots;
    //array of map pointers.
    Map* _maps_array[2];
    
public:
    //constructor
    Game();

    //prints the main menu
    void print_screen();

    //option 1. add new robot
    void game_add_new_robot(const int map_number,const int positionX, const int positionY);

    //option 2. remove a robot
    void game_remove_robot(const int robot_number);

    //option 3. move a robot.
    void game_move_robot(const int robot_number,const char direction);

    //option 4. operator+ on two maps
    void game_operator_plus();

    //option 5. operator+= on two maps. main gives what map to override
    void game_operator_plus_equal(const int map_number_to_override_plus_equal);

    //option 6. operator= on two maps.  main gives what map to override
    void game_operator_equal(const int map_number_to_override_equal);

    //option 7. operator== on two maps.  returns true/false
    bool game_operator_test_if_equal();

    //option 8. print a map and its robots
    void game_operator_print(const int map_number_to_print);

    //option 9. quit.
    void quit();
};
#endif //ASS4_GAME_H