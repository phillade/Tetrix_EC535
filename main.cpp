#include <iostream>
#include "game.h"
#include "block.h"

using namespace std;

int main() {
    std::cout << "Hello, World!" << std::endl;
    //generate a random block
    block thisNewblock = block();
    cout << "The type of block is " << thisNewblock.type << endl;
    cout << "The orientation of the block is " << thisNewblock.orientation1 << endl;
    cout << "The coordinates of the block is " << thisNewblock.texture << endl;
    cout << "The coordinates are " << thisNewblock.coordinates.first << ", " << thisNewblock.coordinates.second << endl;
    return 0;
}