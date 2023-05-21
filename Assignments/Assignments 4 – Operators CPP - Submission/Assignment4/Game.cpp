
#include<iostream>
#include "Map.h"
#include "Robot.h"
#include "Game.h"

using namespace std;



Game::Game()
{
    _maps_array[0] = new Map(1);
    _maps_array[1] = new Map(2);
    vector<Robot*> array_of_robots;
}

void Game::print_screen(){
    cout<<"Robot Control Menu"<<endl;
    cout<<"1. Add Robot"<<endl;
    cout<<"2. Delete Robot"<<endl;
    cout<<"3. Move Robot"<<endl;
    cout<<"4. Operator +"<<endl;
    cout<<"5. Operator +="<<endl;
    cout<<"6. Operator ="<<endl;
    cout<<"7. Operator =="<<endl;
    cout<<"8. Operator <<"<<endl;
    cout<<"9. Quit"<<endl;
    cout<<"Input your option: "<<endl;
}

void Game::game_add_new_robot(const int map_number,const int positionX,const int positionY){
    if (map_number > 2 || map_number < 0) {
        cout << "Invalid MAP number" << endl;
        return;
    }
    Map* pMap = _maps_array[map_number-1];
    if ((*pMap).getLocation(positionY,positionX) == 1 || (*pMap).getLocation(positionY,positionX) == -1)
        cout<<"Invalid location"<<endl;
    else {
        Robot *new_robot = new Robot(map_number, positionX, positionY);
        _array_of_robots.push_back(new_robot);
    }
}

void Game::game_remove_robot(const int robot_number){
    auto robot_iterator = _array_of_robots.begin();
    for (int counterRobots=0;counterRobots<_array_of_robots.size();counterRobots++)
    {
        if ((*robot_iterator)->getRobotId() == robot_number){
            if ((*robot_iterator)->canMove() == true)
                cout<<"Robot deleted: "<<(*robot_iterator)->getRobotId()<<" MAP: "<<(*robot_iterator)->getMapNumber()<<" GPS: "<<(*robot_iterator)->getLocationX()<<","<<(*robot_iterator)->getLocationY()<<endl;
            delete *(robot_iterator);
            _array_of_robots.erase(robot_iterator);
            break;
        }
        else
            robot_iterator++;
    }
}

void Game::game_move_robot(const int robot_number,const char direction)
{
    auto robot_iterator = _array_of_robots.begin();
    for (int counterRobots=0;counterRobots<_array_of_robots.size();counterRobots++)
    {
        if ((*robot_iterator)->getRobotId() == robot_number){
            int robot_map_number = (*robot_iterator)->getMapNumber()-1;
            if ((*robot_iterator)->canMove() == true){
                if (direction == 'R') {
                    if ((*robot_iterator)->getLocationX()+1 == 7)
                        (*robot_iterator)->setCanMove(false);
                    else {
                        if ((*(_maps_array[robot_map_number])).getLocation((*robot_iterator)->getLocationY(),(*robot_iterator)->getLocationX() + 1) == 0)
                            (*robot_iterator)->setLocationX((*robot_iterator)->getLocationX() + 1);
                    }
                }
                else if (direction == 'L') {
                    if ((*robot_iterator)->getLocationX()-1 == -1)
                        (*robot_iterator)->setCanMove(false);
                    else {
                        if ((*(_maps_array[robot_map_number])).getLocation((*robot_iterator)->getLocationY(),
                                                                       (*robot_iterator)->getLocationX() - 1) == 0)
                            (*robot_iterator)->setLocationX((*robot_iterator)->getLocationX() - 1);
                    }
                }
                else if (direction == 'U') {
                    if ((*robot_iterator)->getLocationY()+1 == 7)
                        (*robot_iterator)->setCanMove(false);
                    else {
                        if ((*(_maps_array[robot_map_number])).getLocation((*robot_iterator)->getLocationY()+1,(*robot_iterator)->getLocationX()) == 0)
                            (*robot_iterator)->setLocationY((*robot_iterator)->getLocationY() + 1);
                    }

                }
                else if (direction == 'D') {
                    if ((*robot_iterator)->getLocationY() - 1 == -1)
                        (*robot_iterator)->setCanMove(false);
                    else {
                        if ((*(_maps_array[robot_map_number])).getLocation((*robot_iterator)->getLocationY()-1,(*robot_iterator)->getLocationX()) == 0)
                            (*robot_iterator)->setLocationY((*robot_iterator)->getLocationY() - 1);
                    }
                }
                else
                    cout<<"Incorrect direction"<<endl;
            }
            if ((*robot_iterator)->canMove())
                cout<<"Robot: "<<(*robot_iterator)->getRobotId()<<" MAP: "<<(*robot_iterator)->getMapNumber()<<" GPS: "<<(*robot_iterator)->getLocationX()<<","<<(*robot_iterator)->getLocationY()<<endl;
            break;
        }
        robot_iterator++;
    }
}

void Game::game_operator_plus() {
    Map map_addition = *_maps_array[0] + *_maps_array[1];
    cout<<map_addition;
    auto robot_iterator = this->_array_of_robots.begin();
    for (int counterRobots=0;counterRobots<_array_of_robots.size();counterRobots++)
    {
        if (map_addition.getLocation((*robot_iterator)->getLocationY(), (*robot_iterator)->getLocationX()) == 0){
            if ((*robot_iterator)->canMove())
                cout<<"Robot: "<<(*robot_iterator)->getRobotId()<<" GPS: "<<(*robot_iterator)->getLocationX()<<","<<(*robot_iterator)->getLocationY()<<endl;
        }
        ++robot_iterator;
    }
}

void Game::game_operator_plus_equal(const int map_number_to_override_plus_equal){
    if (map_number_to_override_plus_equal < 0 || map_number_to_override_plus_equal >2 ){
        cout<<"Invalid MAP number"<<endl;
        return;
    }
    else if (map_number_to_override_plus_equal == 1){
        *_maps_array[0] += *_maps_array[1];
    }
    else{ //map_number= 2
        *_maps_array[1] += *_maps_array[0];
    }
    auto robot_iterator = _array_of_robots.begin();
    for (int counterRobots=0;counterRobots<_array_of_robots.size();counterRobots++)
    {
        if ((*_maps_array[map_number_to_override_plus_equal-1]).getLocation((*robot_iterator)->getLocationY(),(*robot_iterator)->getLocationX()) == 1) {
            delete *robot_iterator;
            robot_iterator = (this->_array_of_robots).erase(this->_array_of_robots.begin() + counterRobots);
            counterRobots--;
        } else
            ++robot_iterator;
    }
}

void Game::game_operator_equal(const int map_number_to_override_equal) {
    if (map_number_to_override_equal == 1)
        *_maps_array[0] = *_maps_array[1];
    else if (map_number_to_override_equal == 2)
        *_maps_array[1] = *_maps_array[0];
    else{
        cout<<"Invalid MAP number"<<endl;
        return;
    }
    auto robot_iterator = _array_of_robots.begin();
    for (int counterRobots=0;counterRobots<_array_of_robots.size();counterRobots++)
    {
        if ((*_maps_array[map_number_to_override_equal-1]).getLocation((*robot_iterator)->getLocationY(),(*robot_iterator)->getLocationX()) == 1) {
            robot_iterator = (this->_array_of_robots).erase(this->_array_of_robots.begin() + counterRobots);
        } else
            robot_iterator++;
    }
}

bool Game::game_operator_test_if_equal(){
    return *_maps_array[0] == *_maps_array[1];
}

void Game::game_operator_print(const int map_number_to_print){
    if (map_number_to_print > 2 || map_number_to_print<0 )
    {
        cout<<"Invalid MAP number"<<endl;
        return;
    }
    cout<<*(_maps_array[map_number_to_print-1]);
    auto robot_iterator = this->_array_of_robots.begin();
    for (int counterRobots=0;counterRobots<_array_of_robots.size();counterRobots++)
    {
        if ((*robot_iterator)->getMapNumber() == map_number_to_print){
            if ((*(_maps_array[map_number_to_print - 1])).getLocation((*robot_iterator)->getLocationY(),
                                                                      (*robot_iterator)->getLocationX()) == 0) {
                if ((*robot_iterator)->canMove())
                    cout << "Robot: " << (*robot_iterator)->getRobotId() << " MAP: "
                         << (*robot_iterator)->getMapNumber() << " GPS: " << (*robot_iterator)->getLocationX() << ","
                         << (*robot_iterator)->getLocationY() << endl;
            }
        }
        robot_iterator++;
    }
}

void Game::quit() {
    auto robot_iterator = _array_of_robots.begin();
    for (int counterRobots=0;counterRobots<_array_of_robots.size();counterRobots++)
    {
        delete (*robot_iterator);
        robot_iterator++;
    }
    _array_of_robots.clear();
    delete _maps_array[0];
    delete _maps_array[1];
}