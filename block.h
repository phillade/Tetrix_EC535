//
// Created by Phillip Teng on 2019-04-15.
//
#include <utility> // for pair
#include <iostream> //everything else
#include <cstdlib> //for rand
#include <ctime>
#include <random>

#ifndef TETRIX_EC535_BLOCK_H
#define TETRIX_EC535_BLOCK_H

using namespace std;
struct blockType{
    pair<int, int> up;
    pair<int, int> down;
    pair<int, int> left;
    pair<int, int> right;
    int color;
};

class block {

public:

    //Variables
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

    orientation orientation;
    int color;


    int texture;

    void assignBlockType(int input){

        switch(input){
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

    }

    void assignOrientation(int input){
        switch(input){
            case 0:
                orientation = left;
                break;
            case 1:
                orientation = right;
                break;
            case 2:
                orientation = up;
                break;
            case 3:
                orientation = down;
                break;
            default:
                cout << "You forgot a case" << endl;
        }
    }

    pair<int,int> * blockICoords(){
        switch(orientation)
        {
            case left:
                pair<int,int> array[4] = {{0, 2},{1, 2},{2,2},{3,2}};
                return array;
        }
    };

    pair<int,int> * getCoordinates(){
        pair<int,int> Coord[4];
        switch(type)
        {
            case I:
                return blockICoords();
            case L:
                break;
            case J:
                break;
            case O:
                break;
            case S:
                break;
            case Z:
                break;
            case T:
                break;
            default:
                break;
        }
    };

    //generates a random block
    block(){
        //constructor
        orientation = left;
        type = I;

        //randomly generate a number 0 to 6 for the seven types of blocks

        int blockType = rand()%7;
        assignBlockType(blockType);

        //generate orientation
        int randomOrientation = rand()%4;
        assignOrientation(randomOrientation);

        pair<int, int> coord[4] = getCoordinates();

        //randomly generate the type of block here.
        texture = 0;

    };
};


#endif //TETRIX_EC535_BLOCK_H
