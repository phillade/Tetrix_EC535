//
// Created by Phillip Teng on 2019-04-15.
//

#include "block.h"
#include "grid.cpp"
#include <QApplication>
//#include <QTest>
#include <unistd.h>

#ifndef TETRIX_EC535_GAME_H
#define TETRIX_EC535_GAME_H


class game {
    //grid is
    int grid[10][20];
    //checking if game has ended
    bool gameEnded;
    //for pausing game
    bool paused;

    bool blockInPlay;

    block activeBlock;

public:
    game(){
        //constructor
        blockInPlay = false;
        //game starts
        gameEnded = false;
        paused = false;
        //Game colors
        for (int i = 0; i < 10; i++){
            for(int j = 0; j < 20; j++){
                grid[i][j] = 0;
                //set default color to zero. There are seven predefined colors.
            }
        }

    };
    void inputBlock(block * input, Grid grid){
        //displays the input block on the screen
        //get block type
        pair<int,int> startPt = {5,0};
        input->coord = grid.placeBlock(input->coord, startPt, input->color);
        input->refPt = startPt;


    };

    void rotate(block * input, Grid grid){
        vector<pair<int,int>> oldCoord = input->coord; // save old coords
        input->rotate(); // rotate coords
        grid.replace(oldCoord, input->coord, input->color);
        //rotate block that is in control
    };

    void checkBelow(){
        //checks whether the lock has is the bottom level yet
    }

    void updateLines(){
        //everything
    };

    void checkFilled(){
        //checks whether or not there is a line that is filled

    };

    void updateGrid(){
        //updates the grid. if there is a filled line, it translates all the blocks above the cleared lines down.

    };

    void translate(block * input, Grid grid){
        //translating speed slow or fast
        vector<pair<int,int>> newCoord = input->coord;
        for (int i=0; i<newCoord.size(); i++)
            newCoord[i].second = newCoord[i].second + 1;
        grid.replace(input->coord, newCoord, input->color);
        input->coord = newCoord; // save new coords
        input->refPt.second = input->refPt.second+1; // update ref pt
    };

    int gameSpeed(int * gameEnd){

        int period = 1;

        if (gameEnded){
            *gameEnd = 1;
        }


        //hard coded to run every second
        return period;
    };

    void displayGrid(){
        for (int i = 0; i < 20; i++){
            for (int j = 0; j < 10; j++){
                cout << grid[j][i] << " ";
            }
            cout << endl;
        }
    };

    void pause(){
        paused = true;
    }

    void unpause(){
        paused = false;
    }

    void update(QApplication * app, Grid grid){
        //run the game

        if (!paused){
            //run the game

            if(!blockInPlay){ // no block in play
                // generate block
                activeBlock = block();
                // display block on grid
                inputBlock(&activeBlock, grid);
                cout << "made block!" << endl;
                blockInPlay = 1;
            }
            else{
                //block already in play, translate the block down
                cout << "translated block!" << endl;
                translate(&activeBlock, grid);
                app->processEvents();
                usleep(500000);
                rotate(&activeBlock, grid);
                app->processEvents();
            }
        }

    };
};


#endif //TETRIX_EC535_GAME_H
