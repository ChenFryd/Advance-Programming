//
// Created by Chen on 31-Dec-22.
//

#include "Map.h"
#include <iostream>
#include <string>

using namespace std;
#pragma warning(disable: 4996);


Map::Map(int map_number){
    if (map_number == 1)
    {
        int temp_array[7][7] = {{1,0,0,0,0,0,0},
                                {1,0,1,0,0,1,0},
                                {1,0,1,1,0,1,0},
                                {0,0,0,1,1,1,0},
                                {0,1,0,1,1,1,0},
                                {1,1,0,0,0,0,1},
                                {1,0,0,1,1,0,1}
        };
        for (int i = 0; i < 7; ++i) {
            for (int j = 0; j < 7; ++j) {
                _map_table[i][j] = temp_array[i][j];
            }
        }
    }
    else if (map_number == 2){
        int temp_array[7][7] = {{1,0,1,0,0,0,0},
                                {1,1,0,1,1,1,0},
                                {0,0,0,0,0,1,1},
                                {0,1,1,1,0,1,1},
                                {1,1,0,0,0,1,1},
                                {1,1,0,1,1,1,1},
                                {1,1,0,0,0,1,1}};
        for (int i = 0; i < 7; ++i) {
            for (int j = 0; j < 7; ++j) {
                _map_table[i][j] = temp_array[i][j];
            }
        }
    }
    else
        cout<<"Invalid map number"<<endl;
}

const int Map::getLocation(const int positionY, const int positionX) const {
    if (positionY >6 || positionY <0 || positionX >6 || positionX < 0)
        return -1;
    return this->_map_table[positionY][positionX];
}

void Map::setMapCordinates(const int x, const int y,const int value) {
    if (x < 0 or x>6 or y<0 or y>6) {
        cout<<"Invalid coordinates"<<endl;
        return;
    }
    if (value < 0 || value > 1){
        cout<<"Invalid value to map"<<endl;
        return;
    }
    this->_map_table[x][y] = value;
}

Map Map::operator+(const Map& map_other)const{
    Map new_map = Map();
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 7; ++j) {
            new_map.setMapCordinates(i,j,max(this->_map_table[i][j],map_other.getLocation(i,j)));
        }
    }
    return new_map;
}

Map& Map::operator+=(const Map &map_other) {
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 7; ++j) {
            this->_map_table[i][j] = max(this->_map_table[i][j],map_other.getLocation(i,j));
        }
    }
    return *this;
}
Map& Map::operator=(const Map &map_other) {
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 7; ++j) {
            this->_map_table[i][j] = map_other.getLocation(i,j);
        }
    }
    return *this;
}

const bool Map::operator==(const Map &map_other) {
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 7; ++j) {
            if (this->_map_table[i][j] != map_other.getLocation(i,j))
                return false;
        }
    }
    return true;
}

ostream& operator<<(ostream& out, const Map& map_input){
    for (int i = 6; i >= 0 ; --i) {
        out <<"[";
        for (int j = 0; j < 7; ++j) {
            out<<map_input.getLocation(i,j);
            if (j < 6)
                out<<" ";
        }
        out <<"]"<<endl;
    }
    return out;
}