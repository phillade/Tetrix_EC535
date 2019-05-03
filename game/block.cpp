#include "block.h"

using namespace std;

block::block(){
	/* 
	Constructor for class block. Generates a block of random type & orientation.
	*/

    color = 0; // default color
    
    // randomly generate one of 7 types of blocks
    type = Type(rand()%7);

    // randomly generate one of 4 orientations
    orientation = rand()%4;

    // Get coordinates
    coord = getCoordinates(orientation); // offset by reference pt (references tetris grid)
	zeroedCoord = getCoordinates(orientation); // no offset

    // Offset by ref point
    refPt = make_pair(4,-2); // default
    for (int i=0; i<coord.size(); i++){
        coord[i].first += refPt.first;
        coord[i].second += refPt.second;
    }
}

vector<pair<int, int> > block::blockICoords(Orientation ori){
	/* Get coordinates for block I given orientation. 
	  ARGS:
		ori (Orientation): Requested orientation 

	  RETURN:
		coord (vector<pair<int, int> >): Coordinates of block with requested orientation.
    */
    vector<pair<int, int> > coord;
    switch(ori)
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
}

vector<pair<int, int> > block::blockJCoords(Orientation ori){
	/* Get coordinates for block J given orientation. 
	  ARGS:
		ori (Orientation): Requested orientation 

	  RETURN:
		coord (vector<pair<int, int> >): Coordinates of block with requested orientation.
   */
    vector<pair<int, int> > coord;
    switch(ori)
    {
        case left:
            coord.push_back(make_pair(0,1));
            coord.push_back(make_pair(1,1));
            coord.push_back(make_pair(2,1));
            coord.push_back(make_pair(2,2));
            break;
        case right:
            coord.push_back(make_pair(0,0));
            coord.push_back(make_pair(0,1));
            coord.push_back(make_pair(1,1));
            coord.push_back(make_pair(2,1));
            break;
        case up:
            coord.push_back(make_pair(0,2));
            coord.push_back(make_pair(1,2));
            coord.push_back(make_pair(1,1));
            coord.push_back(make_pair(1,0));
            break;
        default: // down
            coord.push_back(make_pair(1,2));
            coord.push_back(make_pair(1,1));
            coord.push_back(make_pair(1,0));
            coord.push_back(make_pair(2,0));
    }
    return coord;
}

vector<pair<int, int> > block::blockLCoords(Orientation ori){
	/* Get coordinates for block L given orientation. 
	  ARGS:
		ori (Orientation): Requested orientation 

	  RETURN:
		coord (vector<pair<int, int> >): Coordinates of block with requested orientation.
   */
    vector<pair<int, int> > coord;
    switch(ori)
    {
        case left:
            coord.push_back(make_pair(0,1));
            coord.push_back(make_pair(1,1));
            coord.push_back(make_pair(2,1));
            coord.push_back(make_pair(0,2));
            break;
        case right:
            coord.push_back(make_pair(0,1));
            coord.push_back(make_pair(1,1));
            coord.push_back(make_pair(2,1));
            coord.push_back(make_pair(2,0));
            break;
        case up:
            coord.push_back(make_pair(0,0));
            coord.push_back(make_pair(1,0));
            coord.push_back(make_pair(1,1));
            coord.push_back(make_pair(1,2));
            break;
        default: // down
            coord.push_back(make_pair(2,2));
            coord.push_back(make_pair(1,2));
            coord.push_back(make_pair(1,1));
            coord.push_back(make_pair(1,0));
    }
    return coord;
}

vector<pair<int, int> > block::blockOCoords(Orientation ori){
	/* Get coordinates for block O given orientation. 
	  ARGS:
		ori (Orientation): Requested orientation 

	  RETURN:
		coord (vector<pair<int, int> >): Coordinates of block with requested orientation.
   */
    vector<pair<int, int> > coord;
    switch(ori)
    {
        case left:
            coord.push_back(make_pair(0,1));
            coord.push_back(make_pair(1,1));
            coord.push_back(make_pair(0,2));
            coord.push_back(make_pair(1,2));
            break;
        case right:
            coord.push_back(make_pair(0,1));
            coord.push_back(make_pair(1,1));
            coord.push_back(make_pair(0,2));
            coord.push_back(make_pair(1,2));
            break;
        case up:
            coord.push_back(make_pair(0,1));
            coord.push_back(make_pair(1,1));
            coord.push_back(make_pair(0,2));
            coord.push_back(make_pair(1,2));
            break;
        default: // down
            coord.push_back(make_pair(0,1));
            coord.push_back(make_pair(1,1));
            coord.push_back(make_pair(0,2));
            coord.push_back(make_pair(1,2));
    }
    return coord;
}

vector<pair<int, int> > block::blockSCoords(Orientation ori){
	/* Get coordinates for block S given orientation. 
	  ARGS:
		ori (Orientation): Requested orientation 

	  RETURN:
		coord (vector<pair<int, int> >): Coordinates of block with requested orientation.
   */
    vector<pair<int, int> > coord;
    switch(ori)
    {
        case left:
            coord.push_back(make_pair(0,2));
            coord.push_back(make_pair(1,2));
            coord.push_back(make_pair(1,1));
            coord.push_back(make_pair(2,1));
            break;
        case right:
            coord.push_back(make_pair(0,1));
            coord.push_back(make_pair(1,1));
            coord.push_back(make_pair(1,0));
            coord.push_back(make_pair(2,0));
            break;
        case up:
            coord.push_back(make_pair(0,0));
            coord.push_back(make_pair(0,1));
            coord.push_back(make_pair(1,1));
            coord.push_back(make_pair(1,2));
            break;
        default: // down
            coord.push_back(make_pair(1,0));
            coord.push_back(make_pair(1,1));
            coord.push_back(make_pair(2,1));
            coord.push_back(make_pair(2,2));
    }
    return coord;
}

vector<pair<int, int> > block::blockTCoords(Orientation ori){
	/* Get coordinates for block T given orientation. 
	  ARGS:
		ori (Orientation): Requested orientation 

	  RETURN:
		coord (vector<pair<int, int> >): Coordinates of block with requested orientation.
   */
    vector<pair<int, int> > coord;
    switch(ori)
    {
        case left:
                 coord.push_back(make_pair(0,1));
                 coord.push_back(make_pair(1,1));
                 coord.push_back(make_pair(2,1));
                 coord.push_back(make_pair(1,2));
            break;
        case right:
                 coord.push_back(make_pair(0,1));
                 coord.push_back(make_pair(1,1));
                 coord.push_back(make_pair(2,1));
                 coord.push_back(make_pair(1,0));
            break;
        case up:
                 coord.push_back(make_pair(1,2));
                 coord.push_back(make_pair(1,1));
                 coord.push_back(make_pair(1,0));
                 coord.push_back(make_pair(0,1));
            break;
        default: // down
                 coord.push_back(make_pair(1,2));
                 coord.push_back(make_pair(1,1));
                 coord.push_back(make_pair(1,0));
                 coord.push_back(make_pair(2,1));
    }
    return coord;
}

vector<pair<int, int> > block::blockZCoords(Orientation ori){
	/* Get coordinates for block Z given orientation. 
	  ARGS:
		ori (Orientation): Requested orientation 

	  RETURN:
		coord (vector<pair<int, int> >): Coordinates of block with requested orientation.
   */
    vector<pair<int, int> > coord;
    switch(ori)
    {
        case left:
                 coord.push_back(make_pair(0,1));
                 coord.push_back(make_pair(1,1));
                 coord.push_back(make_pair(1,2));
                 coord.push_back(make_pair(2,2));
            break;
        case right:
                 coord.push_back(make_pair(0,0));
                 coord.push_back(make_pair(1,0));
                 coord.push_back(make_pair(1,1));
                 coord.push_back(make_pair(2,1));
            break;
        case up:
                 coord.push_back(make_pair(0,2));
                 coord.push_back(make_pair(0,1));
                 coord.push_back(make_pair(1,1));
                 coord.push_back(make_pair(1,0));
            break;
        default: // down
                 coord.push_back(make_pair(1,2));
                 coord.push_back(make_pair(1,1));
                 coord.push_back(make_pair(2,1));
                 coord.push_back(make_pair(2,0));
    }
    return coord;
}

vector<pair<int, int> > block::getCoordinates(int ori){
	/* Get coordinates for block with specified orientation.

	   ARGS: 
		ori (int): Orientation of block to get coordinates for.

	   RETURN
		Coordinates of block with specified orientation.
   	*/
    switch(type)
    {
        case I:
            return blockICoords(Orientation(ori));
        case L:
            return blockLCoords(Orientation(ori));
        case J:
            return blockJCoords(Orientation(ori));
        case O:
            return blockOCoords(Orientation(ori));
        case S:
            return blockSCoords(Orientation(ori));
        case Z:
            return blockZCoords(Orientation(ori));
        case T:
            return blockTCoords(Orientation(ori));
        default:
            break;
    }
}

int block::rotateOrientation(int oldOri, int direction){
    /*
     Get orientation of block if rotated. But do not actually rotate block! 
	 * direction = 0 : rotate right
     * direction = 1 : rotate left

     ARGS:
     	oldOri (int): Orientation of block that will be rotated
     	direction (int): Direction to rotate the block

 	RETURN:
 		newOri (int): Orientation of block after rotation
    */
    int newOri;
    if (direction){
        if (oldOri == 3)
            newOri = 0;
        else
            newOri = orientation + 1;
    } else {
        if (oldOri == 0)
            newOri = 3;
        else
            newOri = orientation - 1;
    }
    return newOri;
}

vector<pair<int, int> > block::getRotateCoord(int direction){
    /* 
     Get coordinates of block if rotated. But do not actually rotate block!
     * direction = 0 : rotate right
     * direction = 1 : rotate left

     ARGS: 
     	direction (int): Direction to rotate the block

 	RETURN:
 		Coordinates of rotated block
     */
    // Get new orientation
    int newOri = rotateOrientation(orientation, direction);

    // Get coordinates of rotated block
    vector<pair<int, int> > newCoord = getCoordinates(newOri);

    // add ref point to coords to calculate true coords on tetris grid
    for (int i=0; i<newCoord.size(); i++){
        newCoord[i].first += refPt.first;
        newCoord[i].second += refPt.second;
    }
    return newCoord;
}

void block::setBlock(int ori, vector<pair<int, int> > newCoord){
	/*
		Set block orientation and coordinates.

		ARGS: 
			ori (int): Orientation to set block to
			newCoord (vector<pair<int, int> >): Coordinates to set block to

		Return:
			void
	*/
    orientation = ori; // set new orientation
    coord = newCoord; // set new Coord
}

