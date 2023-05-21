//
// Created by Chen on 01-Jan-23.
//
#include "Game.h"
#include "string.h"
#include <iostream>
using namespace std;

int main() {
    char userInput[200];
    int choice = 0;
    Game game_main = Game();
    while(choice != 9)
    {
        game_main.print_screen();
        cin>>userInput;
        int length_input = strlen(userInput);
        if (length_input==1 && isdigit(userInput[0])) {
            choice = stoi(userInput);
        }
        else{
            cout<<"Invalid input"<<endl;
            choice = 0;
        }

        switch (choice) {
            case 1:{
                cout<<"Enter MAP number: "<<endl;
                int curr_map_robot,curr_robot_x,curr_robot_y;
                cin>>curr_map_robot;
                cout<<"Enter Coordinates (X,Y): "<<endl;
                cin>>curr_robot_x>>curr_robot_y;
                game_main.game_add_new_robot(curr_map_robot,curr_robot_x,curr_robot_y);
                break;
            }

            case 2: { //delete robot
                cout << "Enter Robot number: " << endl;
                int robot_id_to_delete;
                cin >> robot_id_to_delete;
                game_main.game_remove_robot(robot_id_to_delete);
                break;
            }

            case 3: { //move robot
                cout << "Enter Robot number: " << endl;
                int robot_number_to_move;
                cin >> robot_number_to_move;
                char direction_to_move_robot;
                cout << "Enter direction: " << endl;
                cin >> direction_to_move_robot;
                game_main.game_move_robot(robot_number_to_move, direction_to_move_robot);
                break;
            }

            case 4: { //operator +
                game_main.game_operator_plus();
                break;
            }

            case 5: { //operator +=
                cout << "Override MAP number: " << endl;
                int map_number_to_override_plus_equal;
                cin >> map_number_to_override_plus_equal;
                game_main.game_operator_plus_equal(map_number_to_override_plus_equal);
                break;
            }

            case 6: {//operator =
                cout << "Override MAP number: " << endl;
                int map_number_to_override_equal;
                cin >> map_number_to_override_equal;
                game_main.game_operator_equal(map_number_to_override_equal);
                break;
            }

            case 7: { //operator ==
                bool output_test_equal = game_main.game_operator_test_if_equal();
                if (output_test_equal)
                    cout << "TRUE" << endl;
                else
                    cout << "FALSE" << endl;
                break;
            }

            case 8: { //operator >>
                cout << "Please enter MAP number: "<<endl;
                int map_number_to_print;
                cin >> map_number_to_print;
                game_main.game_operator_print(map_number_to_print);
                break;
            }

            case 9: { //quit
                game_main.quit();
                break;
            }

            default:
                break;
        }
    }
    return 0;
}