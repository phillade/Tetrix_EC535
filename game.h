//
// Created by Phillip Teng on 2019-04-15.
//

#include "block.h"

#ifndef TETRIX_EC535_GAME_H
#define TETRIX_EC535_GAME_H


class game {
    //grid is
    int grid[10][20];
    bool gameEnded;
    bool paused;
    bool blockInPlay;
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
    void inputBlock(block input){
        //displays the input block on the screen
        //get block type


    };

    void rotote(){
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

    void translate(){
        //translating speed slow or fast

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
    void update(){
        //run the game

        if (!paused){
            //run the game

            if(!blockInPlay){
                // if no block in play, generate a block
                block NewBlock = block();
                inputBlock(NewBlock);
            }
        }

    };
};


#endif //TETRIX_EC535_GAME_H
