#include <iostream>
#include "game.h"
#include "block.h"
#include <ctime>
#include <unistd.h>

using namespace std;

int main() {
    std::cout << "Hello, World!" << std::endl;
    //generate a random block
    block thisNewblock = block();
    thisNewblock = block();
    thisNewblock = block();
    thisNewblock = block();
    thisNewblock = block();
    thisNewblock = block();

    cout << "The type of block is " << thisNewblock.type << endl;
    cout << "The coordinates of the block is " << thisNewblock.texture << endl;
    int gameEnd = 1;
    srand(time(nullptr));

    //create a game object
    game Machine = game();

    while (gameEnd){
        Machine.displayGrid();
        int period = Machine.gameSpeed(&gameEnd);
        Machine.update();
        cout << endl;
        sleep(period);
    }



    return 0;
}