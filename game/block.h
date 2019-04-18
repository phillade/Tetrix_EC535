//
// Created by Phillip Teng on 2019-04-15.
//
#include <utility> // for pair
#include <iostream> //everything else
#include <cstdlib> //for rand
#include <ctime>
#include <vector>
//#include <random>

#ifndef TETRIX_EC535_BLOCK_H
#define TETRIX_EC535_BLOCK_H

using namespace std;

class block {
    enum Type {
        //The explanations to the type of the block is found here
        //https://tetris.fandom.com/wiki/Tetromino
        I, J, L, O, S, T, Z
    };

    enum Orientation{
        left, up, right, down
    };
public:
    //Variables
    Type type;
    int orientation;
    //Orientation orientation;
    vector<pair<int, int> > coord;
    pair<int,int> refPt;

    string color;

    vector<pair<int, int> > blockICoords(){
        vector<pair<int, int> > coord;
        switch(Orientation(orientation))
        {
            case left:
					 coord.push_back(make_pair(0,2));
					 coord.push_back(make_pair(1,2));
					 coord.push_back(make_pair(2,2));
					 coord.push_back(make_pair(3,2));
                break;
            case right:
					 coord.push_back(make_pair(0,1));
					 coord.push_back(make_pair(1,1));
					 coord.push_back(make_pair(2,1));
					 coord.push_back(make_pair(3,1));
                break;
            case up:
					 coord.push_back(make_pair(1,0));
					 coord.push_back(make_pair(1,1));
					 coord.push_back(make_pair(1,2));
					 coord.push_back(make_pair(1,3));
                break;
            default: // down
					 coord.push_back(make_pair(2,0));
					 coord.push_back(make_pair(2,1));
					 coord.push_back(make_pair(2,2));
					 coord.push_back(make_pair(2,3));
        }
        return coord;
    };

    vector<pair<int, int> > getCoordinates(){
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

    void rotate(){
        if (orientation == 3)
            orientation = 0;
        else
            orientation = orientation + 1;
        coord = getCoordinates();
        // add ref point
        for (int i=0; i<coord.size(); i++){
            coord[i].first += refPt.first;
            coord[i].second += refPt.second;
        }
    };


    //generates a random block
    block(){
        color = "red";

        //randomly generate a number 0 to 6 for the seven types of blocks
        //type = rand()%7;
        type = I;

        //generate orientation
        orientation = Orientation(rand()%4);

        coord = getCoordinates();

        refPt = make_pair(0,0);

    };
};


#endif //TETRIX_EC535_BLOCK_H
