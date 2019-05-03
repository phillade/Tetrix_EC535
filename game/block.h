#ifndef TETRIX_EC535_BLOCK_H
#define TETRIX_EC535_BLOCK_H

#include <utility> // for pair
#include <iostream> //everything else
#include <cstdlib> //for rand
#include <ctime>
#include <vector>

#define RIGHT 1 // for rotating left
#define LEFT 0 // for rotating right

using namespace std;

class block {

public:
    enum Type { // Type of block
        //The explanations to the type of the block is found here
        //https://tetris.fandom.com/wiki/Tetromino
        I, J, L, O, S, T, Z
    };

    enum Orientation{ // Only for readibility
        left, down, right, up
    };  

    Type type; // type of block
    int orientation; // block orientation
    vector<pair<int, int> > coord; // coords of block w/ offset
    vector<pair<int, int> > zeroedCoord; // coords of block w/o offset
    pair<int,int> refPt; // block offset
    int color; // color of block

    // Generates a block of random orientation and type
    block();

    // Get coordinates for block I given orientation
    vector<pair<int, int> > blockICoords(Orientation ori);;

    // Get coordinates for block J given orientation
    vector<pair<int, int> > blockJCoords(Orientation ori);

    // Get coordinates for block L given orientation
    vector<pair<int, int> > blockLCoords(Orientation ori);

    // Get coordinates for block O given orientation
    vector<pair<int, int> > blockOCoords(Orientation ori);

    // Get coordinates for block S given orientation
    vector<pair<int, int> > blockSCoords(Orientation ori);

    // Get coordinates for block T given orientation
    vector<pair<int, int> > blockTCoords(Orientation ori);

    // Get coordinates for block Z given orientation
    vector<pair<int, int> > blockZCoords(Orientation ori);

    // Get coordinates for block Object's block type given orientation
    vector<pair<int, int> > getCoordinates(int ori);

    // Get orientation if block rotated
    int rotateOrientation(int oldOri, int direction);

    // Get coordinates if block rotated
    vector<pair<int, int> > getRotateCoord(int direction);

    // Set orientation and coordinates of block
    void setBlock(int ori, vector<pair<int, int> > newCoord);

};


#endif //TETRIX_EC535_BLOCK_H
