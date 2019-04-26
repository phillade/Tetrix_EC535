//
// Created by Phillip Teng on 2019-04-15.
//

#include "block.h"
#include "grid.cpp"
#include <QApplication>

//#include <unistd.h>

#ifndef TETRIX_EC535_GAME_H
#define TETRIX_EC535_GAME_H

class game {
    // occupancy of each cell in grid
    int state[10][20];
    // color of each cell in grid
    int colorState[10][20];
    // number of filled blocks for each row
    int rowState[20];
    //checking if game has ended
    bool gameEnded;
    //for pausing game
    bool paused;

    bool blockInPlay;

    block activeBlock;

    bool rowToRemove;

    string Color[8];

public:
    game(){
        //constructor
        blockInPlay = false;
	rowToRemove = false;
        //game starts
        gameEnded = false;
        paused = false;
	string colorLegend[8] = {"lightgray", "red", "blue", "green", "yellow", "purple","black", "orange"};
	for(int i = 0; i < 8; i++){
		Color[i] = colorLegend[i];
	}

        //Grid occupancy and colors
        for (int i = 0; i < 10; i++){
            for(int j = 0; j < 20; j++){
                state[i][j] = 0;
                colorState[i][j] = 0;
            }
        }

        // No blocks in any rows at start of game
        for (int i=0; i<20; i++)
            rowState[i] = 0;

    };

    void rotate(block * input, Grid grid, int direction){
        /* direction = 0 : rotate right
         * direction = 1 : rotate left
         */
        // Get new orientation
        vector<pair<int, int> > rotatedCoord = input->getRotateCoord(direction);
        bool boundCheck = checkBoundary(rotatedCoord); // Check if can rotate coords
        if (!boundCheck){ // if pass
            int ori = input->rotateOrientation(input->orientation, direction); // get orientation after rotate
            grid.replaceBlock(input->coord, rotatedCoord, Color[input->color]); // rotate block in grid
            input->setBlock(ori, rotatedCoord); // save new orientation and rotated coords
        }
    };

    void installBlock(vector<pair<int, int> > coord, Grid grid){
        // Record block locations in state
        bool createNewBlock = false;
        int x, y;
        for (int i=0; i<coord.size(); i++){
            x = coord[i].first;
            y = coord[i].second;
            state[x][y] = 1;

            // Update * blocks in rows
            rowState[y] += 1;

            if (rowState[y] == 10)
                rowToRemove = true;
        }
        //blockInPlay = false; // inactivate block
        generateNewBlock(grid);
    }

    bool checkBoundary(vector<pair<int, int> > coord){
        // Check if bordering boundary
        int x, y;
        for (int i=0; i<coord.size(); i++){
            x = coord[i].first;
            y = coord[i].second;

            if (state[x][y] == 1 || x >= 10 || x < 0 || y >= 20)
                return true;
        }
        return false;
    }

    void translateY(block * input, Grid grid){
        // translating speed slow or fast
        vector<pair<int, int> > newCoord = input->coord; // translated coords
        for (int i=0; i<newCoord.size(); i++)
            newCoord[i].second = newCoord[i].second + 1;
		
		bool boundCheck = checkBoundary(newCoord); // check overlap
        if (boundCheck){ // if bordering boundary, install block in state array
            installBlock(input->coord, grid); // installs block in state array & makes new block
			return;
		}
        // Translate block down in grid
        grid.replaceBlock(input->coord, newCoord, Color[input->color]);
        input->coord = newCoord; // save new coords
        input->refPt.second = input->refPt.second+1; // update block's ref pt
    };

    void translateX(block * input, Grid grid, int direction){
        /*
         * direction = 0 : right
         * direction = 1 : left
         */
        // translating speed slow or fast
        vector<pair<int, int> > newCoord = input->coord; // translated coords

        // Set increment direction
        int increment;
        if (direction == 0)
            increment = 1;
        else
            increment = -1;
        // Calculate coords
        for (int i=0; i<newCoord.size(); i++){
            newCoord[i].first = newCoord[i].first + increment;
        }

        // Check if translated coords border boundary
        bool boundCheck = checkBoundary(newCoord); // check overlap
        if (boundCheck) // if bordering boundary, do nothing
            return;

        // Translate horizontally in grid
        grid.replaceBlock(input->coord, newCoord, Color[input->color]);
        input->coord = newCoord; // save new coords
        input->refPt.first = input->refPt.first+increment; // update block's ref pt

    };

    void rowRemoval(Grid grid){
        int numChanges = 0;
        int newState[10][20];
        int newColorState[10][20];

        vector<int> rowsToDelete;
        // New locations of rows
        int newRowLoc[20];
        for(int i=0; i<20; i++)
            newRowLoc[i] = i;

        // Find new row assignments
        for (int i=0; i < 20; i++){
            if (rowState[i] == 10){ // row filled
                // delete row
                rowState[i] = 0;
                rowsToDelete.push_back(i);
                newRowLoc[i] = -1;
                // Record new row locations of rows that will be shifted down
                for (int j=i+1; j<20; j++){ // only shift rows above deleted row
                    if (newRowLoc[j] == -1)
                        continue;
                    newRowLoc[j] -= 1;
                }
            }
        }

        // Create new state and new color state based on new row assignments
        int newRow;
        for (int i=0; i<20; i++){
            if (newRowLoc[i] == -1){ // clear row
                for (int j=0; j<10; j++){
                    newState[j][i] = 0;
                    newColorState[j][i] = 0;
                }
            } else { // copy row to new grid
                newRow = newRowLoc[i];
                for (int j=0; j<10; j++){
                    newState[j][newRow] = state[j][i];
                    newColorState[j][newRow] = colorState[j][i];
                }
            }
        }

        // Update state and grid
        for (int i=0; i<10; i++){
            for (int j=0; j<20; j++){
                state[i][j] = newState[i][j];
                colorState[i][j] = newColorState[i][j];
                // Update grid
                grid.setCellColor(i,j,Color[colorState[i][j]]);
            }
        }

        rowToRemove = false;
    }

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
                cout << state[j][i] << " ";
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

    void generateNewBlock(Grid grid){
        activeBlock = block();
        activeBlock.color = (int) activeBlock.type + 1; // use type of block to index into  Color array
        // display block on grid
        grid.placeBlock(activeBlock.coord, Color[activeBlock.color]);
    }

    void update(QApplication * app, Grid grid, bool isRotate = false, int rotateDir = RIGHT, bool isXmove = false, int xDir = RIGHT){
        //run the game
        if (!paused){
            //run the game

            if(!blockInPlay){ // no block in play
                generateNewBlock(grid);
                blockInPlay = 1;
            }
            else{
                //block already in play, translate the block down
				if (isRotate){
					rotate(&activeBlock, grid, rotateDir);
				 	app->processEvents();
				} else if (isXmove){
					translateX(&activeBlock, grid, xDir);
					app->processEvents();		
				} else {
                    translateY(&activeBlock, grid);
                    app->processEvents();
				}

	    	}
		}
    };
};


#endif //TETRIX_EC535_GAME_H
