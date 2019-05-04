#include "game.h"
#include "block.h"

game::game(){
    /* 
    	Constructor for class game. No blocks in play & uses original color setting.
    */
	hasStarted = false; // has not started game
    blockInPlay = false; // block in play
    rowsRemoved = 0; // no rows removed  
	rowToRemove = false; // if there is a row to remove
    gameEnded = false; // if game has ended
    paused = false; // if game is paused
	mode = 0; // default color setting
	setColor(mode); // set block colors

    // Initialize grid occupancy and colors
    for (int i = 0; i < 10; i++){
        for(int j = 0; j < 20; j++){
            state[i][j] = 0;
            colorState[i][j] = 0;
        }
    }

    // No blocks in any rows at start of game
    for (int i=0; i<20; i++)
        rowState[i] = 0;
}

int game::getRowsRemoved(){
	/*
		Get the number of rows removed since last check.
	*/
	int newRowsRemoved = rowsRemoved;
	rowsRemoved = 0; // reset
	return newRowsRemoved;
}

void game::rotate(block * input, Grid grid, int direction){
    /*
	  Rotate block.
     * direction = 0 : rotate right
     * direction = 1 : rotate left

     ARGS:
     	input (block*): Block object to rotate
     	grid (Grid): QT grid to update
     	direction (int): direction to rotate block

     RETURN:
     	void
    */
    
    // Get coords at new orientation
    vector<pair<int, int> > rotatedCoord = input->getRotateCoord(direction);
    // Check whether the rotated coords satisfy boundary conditions
    bool boundCheck = checkBoundary(rotatedCoord); 
    if (!boundCheck){ // if can rotate coords
        int ori = input->rotateOrientation(input->orientation, direction); // get orientation after rotate
        grid.replaceBlock(input->coord, rotatedCoord, Color[input->color]); // rotate block in grid
        input->setBlock(ori, rotatedCoord); // save new orientation and rotated coords
    }
}

void game::installBlock(block * input, Grid grid){
	/*
		Install block in state array. 

	ARGS:
     	input (block*): Block object to rotate
     	grid (Grid): QT grid to update
     	
     RETURN:
     	void
	*/
    int x, y;
    for (int i=0; i<input->coord.size(); i++){
    	// Get block coordinate
        x = input->coord[i].first;
        y = input->coord[i].second;
        // Set state & colorState at coord
        state[x][y] = 1;
        colorState[x][y] = input->color;

        // Increment # blocks filled in row 
        rowState[y] += 1;
        // Check if need to remoe row
        if (rowState[y] == 10)
            rowToRemove = true;
    }
    
    // generate new block
    generateNewBlock(grid);
}

bool game::checkBoundary(vector<pair<int, int> > coord){
	/*
		Check if coordinates satisfy boundary conditions.

	ARGS:
     	coord (vector<pair<int, int> >): Coordinates of block

     RETURN:
     	True if boudary conditions failed
	*/
    int x, y;
    for (int i=0; i<coord.size(); i++){
    	// Get coordinate
        x = coord[i].first;
        y = coord[i].second;
		if (y < 0) // Ignore if coord beyond roof of grid (so block can slide down from the top)
			continue;
        if (state[x][y] == 1 || x >= 10 || x < 0 || y >= 20) // check if state at coordinate taken & if w/in bounds 
            return true; // conditions FAILED
    }
    return false; // conditions SUCCESS
}

void game::translateY(block * input, Grid grid){
	/*
	Translate block vertically down by 1. 

	ARGS:
     	input (block*): Block object to rotate
     	grid (Grid): QT grid to update
     	
     RETURN:
     	void 
	*/
    vector<pair<int, int> > newCoord = input->coord; // coords to translate
    for (int i=0; i<newCoord.size(); i++) // translate coord down by 1
        newCoord[i].second = newCoord[i].second + 1;
	
	bool boundCheck = checkBoundary(newCoord); // check boundary conditions
    if (boundCheck){ // if condiitions failed
        installBlock(input, grid); // installs block in state array & makes new block
		return;
	}
    // Translate block down in grid
    grid.replaceBlock(input->coord, newCoord, Color[input->color]); // update tetris grid
    input->coord = newCoord; // save new coords
    input->refPt.second = input->refPt.second+1; // update block's ref pt
}

void game::translateX(block * input, Grid grid, int direction){
    /*
	Translate block horizontally by 1. 
	* direction = 0: right
	* direction = 1: left

	ARGS:
     	input (block*): Block object to rotate
     	grid (Grid): QT grid to update
     	
     RETURN:
     	void 
	*/

    vector<pair<int, int> > newCoord = input->coord; // coords to translate

    // Set direction to translate
    int increment;
    if (direction == 0)
        increment = 1;
    else
        increment = -1;
    // Calculate translated coords
    for (int i=0; i<newCoord.size(); i++){
        newCoord[i].first = newCoord[i].first + increment;
    }

    // Check if translated coords satisfy boundary conditions
    bool boundCheck = checkBoundary(newCoord); 
    if (boundCheck) // conditions failed
        return;

    // Translate horizontally in grid
    grid.replaceBlock(input->coord, newCoord, Color[input->color]); // update tetris grid
    input->coord = newCoord; // save new coords
    input->refPt.first = input->refPt.first+increment; // update block's ref pt

}

void game::rowRemoval(Grid grid){
	/*
		Remove rows that are full.

		Args:
			grid (Grid): QT grid to update. 
	*/

	// Declare new variables
	int newRowState[20]; 
    int newState[10][20];
    int newColorState[10][20];
	int newRowLoc[20];
    vector<int> rowsToDelete;

	// initialize new variables w/ 0's
	for (int i=0; i<10; i++){
		for (int j=0; j<20; j++){
			newState[i][j] = 0;
			newColorState[i][j] = 0;
			if (i == 0){
				newRowLoc[j] = j;
				newRowState[j] = 0;				
			}			
		}		
	}		
	
    // Find new row assignments
    for (int i=0; i < 20; i++){
        if (rowState[i] == 10){ // row filled
            // delete row
            rowsToDelete.push_back(i);
            newRowLoc[i] = -1;
            // Record new row locations of rows that will be shifted down
            for (int j=i-1; j>=0; j--){ // only shift rows above deleted row
                if (newRowLoc[j] == -1){
                	cout << "inside " << j << endl;
                    continue;
                    }
                newRowLoc[j] += 1;
				cout << "shifting down row " << j << endl;
            }
        }
    }
    
    // Set # of rows that will be removed
	rowsRemoved = rowsToDelete.size();

    // Create new state and new color state based on new row assignments
    int newRow;
    for (int i=0; i<20; i++){
		if (newRowLoc[i] != -1){  // if not one of the rows to delete            
			newRow = newRowLoc[i]; // get new row assigned
            for (int j=0; j<10; j++){
                newState[j][newRow] = state[j][i]; // put original row into new row
                newColorState[j][newRow] = colorState[j][i]; 
            }
			newRowState[newRow] = rowState[i];
        }
    }

    // Update state and grid
    for (int i=0; i<10; i++){
        for (int j=0; j<20; j++){
            state[i][j] = newState[i][j];
            colorState[i][j] = newColorState[i][j];
            // Update tetris grid
            grid.setCellColor(i,j,Color[colorState[i][j]]);
			if (i == 0)
				rowState[j] = newRowState[j];
        }
    }

    rowToRemove = false; // no longer any rows to removed
}

void game::generateNewBlock(Grid grid){
	/*
	Generate new block. 

	ARGS:
		grid (Grid): QT grid to update

	RETURN:
		void
	*/
	if (hasStarted == false){ // if we haven't started the game yet
		// Generate block for current & next block
		activeBlock = block(); // current block
		waitingBlock = block(); // next block, for next block display during game
		hasStarted = true;
	} else {
		activeBlock = waitingBlock; // set next block as current block
		waitingBlock = block(); 
	}
    // set block colors with block type
    activeBlock.color = (int) activeBlock.type + 1;
	waitingBlock.color = (int) waitingBlock.type + 1;  

	// check if satisfy boundary conditions
    bool boundCheck = checkBoundary(activeBlock.coord); 
    if (boundCheck) // condition failed, then game has ended
    	gameEnded = true;
    
    // display block on tetris grid
    grid.placeBlock(activeBlock.coord, Color[activeBlock.color]);
}

vector<pair<int, int> > game::getNextCoord(){
	/* Get coordinates of next block */
	return waitingBlock.zeroedCoord;	
}

string game::getNextColor(){
	/* Get color of next block */
	return Color[waitingBlock.color];	
}

void game::hardDrop(block * input, Grid grid){
	// See how far block can drop until boundary conditions failed
	int incr = 0;
	vector<pair<int, int > > tempCoord = input->coord;		
	while (!checkBoundary(tempCoord)){
		incr++;
		for (int i=0; i<tempCoord.size(); i++)
			tempCoord[i].second++;
	}

	// Get new coordinates 
	for (int i=0; i < input->coord.size(); i++){
		tempCoord[i].second = input->coord[i].second + incr-1;		
	}

	grid.replaceBlock(input->coord, tempCoord, Color[input->color]); // Update tetris grid
    input->coord =  tempCoord; // save new coords
	installBlock(input, grid); // save block in state array & tetris grid
}

void game::update(QApplication * app, Grid grid, bool isRotate, int rotateDir, bool isXmove, int xDir, bool isHardDrop){
    /* 
    Update game state: rotate vertically || horizontally OR rotate right || left  OR hard drop!

    ARGS:
    	app (QApplication *): QApplication object to update
    	grid (Grid): QT grid to update
    	isRotate (bool): if choose to rotate
    	rotateDir (int): direction to rotate if isRotate is set to true
    	isXmove (bool): if choose to translate horizontally
    	xDir (int): direction to translate if isXmove is true
    	isHardDrop (bool): if choose to hard drop

	RETURN:
		void
    */
    if (gameEnded) // do nothing if game has ended
    	return;
    else{ 
	    // Remove rows if any rows full
		if (rowToRemove){
			std::cout << "Removing a row" << std::endl;
			rowRemoval(grid);
		}
			
        if(!blockInPlay){ // no block in play
            generateNewBlock(grid); // make new block
            blockInPlay = 1;
        }
        else{
            //block already in play, translate the block down
			if (isRotate){ // rotate block 
				rotate(&activeBlock, grid, rotateDir);
			 	app->processEvents();
			} else if (isXmove){ // translate block horizontally
				translateX(&activeBlock, grid, xDir);
				app->processEvents();		
			} else if (isHardDrop) { // hard drop (drop down quickly)
				hardDrop(&activeBlock, grid);
				app->processEvents();				
			} else { // translate block vertically
                translateY(&activeBlock, grid);
                app->processEvents();
			}

    	}
	}
}

void game::setColor(int modeInput){
	/* 
		Set color scheme of blocks in game
	
		ARGS:
			modeInput (int): color scheme setting to choose

		RETURN:
			void
	*/
	// default color scheme (in original tetris)
	string colorLegend0[8] = {"lightgray", "cyan", "orange", "blue", "yellow", "red","magenta", "green"};
	// black and white color scheme
	string colorLegend1[8] = {"lightgray", "black", "black", "black", "black", "black", "black", "black"};
	// transparent color scheme
	string colorLegend2[8] = {"lightgray", "lightgray", "lightgray", "lightgray", "lightgray", "lightgray", "lightgray", "lightgray"};
	// Set color array to use
	for(int i = 0; i < 8; i++){
		if (modeInput == 0)
			Color[i] = colorLegend0[i];
		else if (modeInput == 1)
			Color[i] = colorLegend1[i];
		else
			Color[i] = colorLegend2[i];
	}
}


void game::restart(Grid grid){
	/*
		Clear everything & restart game.

		grid (Grid): QT grid to be cleared
	*/
	// Reset all variables
	blockInPlay = false; 
    rowsRemoved = 0; 
	rowToRemove = false;
    gameEnded = false;
    paused = false;

    // Reset grid occupancy and colors
    for (int i = 0; i < 10; i++){
        for(int j = 0; j < 20; j++){
            state[i][j] = 0;
            colorState[i][j] = 0;
			grid.setCellColor(i,j, "lightgray");
        }
    }

    // No blocks in any rows at start of game
    for (int i=0; i<20; i++)
        rowState[i] = 0;

	setColor(mode); // set color scheme
}	
