//
// Created by Phillip Teng on 2019-04-15.
//
#include <utility> // for pair
#include <iostream> //everything else
#include <cstdlib> //for rand
#include <ctime>

#ifndef TETRIX_EC535_BLOCK_H
#define TETRIX_EC535_BLOCK_H

using namespace std;

class block {
public:
    //private variables
    //The type of the block
    enum type {
        //The explanations to the type of the block is found here
        //https://tetris.fandom.com/wiki/Tetromino
        I, J, L, O, S, T, Z
    };
    type type;
    enum orientation{
        left, right, up, down
    };
    orientation orientation1;
    int texture;
    std::pair <int, int> coordinates;

    //generates a random block
    block(){
        orientation1 = left;
        type = I;
        //initialize seed for random generator
        srand (time(nullptr));

        //randomly generate a number 0 to 6 for the seven types of blocks
        int blockType = random() % 7;
        switch(blockType){
            case 0:
                type = I;
                break;
            case 1:
                type = J;
                break;
            case 2:
                type = L;
                break;
            case 3:
                type = O;
                break;
            case 4:
                type = S;
                break;
            case 5:
                type = T;
                break;
            case 6:
                type = Z;
                break;
            default:
                cout << "You forgot a case" << endl;
        }

        //randomly generate the type of block here.
        texture = 0;
        coordinates = std::pair<int, int>(0, 0);
    };
};


#endif //TETRIX_EC535_BLOCK_H
