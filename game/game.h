#ifndef TETRIX_EC535_GAME_H
#define TETRIX_EC535_GAME_H

#include "block.h"
#include "grid.cpp"
#include <QApplication>
#include <iostream>

using namespace std;

class game {
    // occupancy of each cell in grid
    int state[10][20];
    // color of each cell in grid
    int colorState[10][20];
    // number of filled blocks for each row
    int rowState[20];
    //for pausing game
    bool paused;
    // if there is an active block
    bool blockInPlay;
    // block objects for current & next blocks
    block activeBlock;
	block waitingBlock;
    // if game has started
	bool hasStarted;
    // if there are rows to remove
    bool rowToRemove;
    // color scheme
    string Color[8];
    // # rows removed since last checked
    int rowsRemoved;

public:
    bool gameEnded;
	int mode;
    game();
    
    int getRowsRemoved();

    void rotate(block * input, Grid grid, int direction);

    void installBlock(block * input, Grid grid);

    bool checkBoundary(vector<pair<int, int> > coord);

    void translateY(block * input, Grid grid);

    void translateX(block * input, Grid grid, int direction);

    void rowRemoval(Grid grid);

    int gameSpeed(int * gameEnd);

    void displayGrid();

    void pause();

    void unpause();

    void generateNewBlock(Grid grid);
	
	vector<pair<int, int> > getNextCoord();

	string getNextColor();

	void hardDrop(block * input, Grid grid);

    void update(QApplication * app, Grid grid, bool isRotate = false, int rotateDir = RIGHT, bool isXmove = false, int xDir = RIGHT, bool isHardDrop = false);
	
	void setColor(int modeInput);

	void restart(Grid grid);

};


#endif //TETRIX_EC535_GAME_H
