#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <iostream>
//#include <QTest>
#include <unistd.h>

//#include "grid.cpp"
#include "score.cpp"

#include "game.h"
#include "block.h"
#include <ctime>

int main(int argc, char **argv)
{
    QApplication * app = new QApplication(argc, argv);

    /////////// Create Grid ////////////
    Grid newGrid;
    QFrame * gridWidget = newGrid.getWidget();

    ///////////// Add score box /////////////
    Score newScore;
    QLabel * scoreLabel = newScore.getLabel();

    ////////// Create main widget (widget that is displayed) /////////////////
    QWidget * main = new QWidget();
    // Layout
    QVBoxLayout* centralLayout = new QVBoxLayout();
    // Add widgets to layout
    centralLayout->addWidget(gridWidget);
    centralLayout->addWidget(scoreLabel);
    // Add layout to main widget
    main->setLayout(centralLayout);

    main->show();


    /////////////////////////////////////////////////////////////////////
    ///////////////////////////// Gameplay //////////////////////////////
    /////////////////////////////////////////////////////////////////////

    std::cout << "Hello, World!" << std::endl;
    //generate a random block
    block thisNewblock = block();

    cout << "The type of block is " << thisNewblock.type << endl;

    int gameEnd = 1;
    srand(time(nullptr));

    //create a game object
    game Machine = game();

    while (gameEnd){
        //Machine.displayGrid();
        //int period = Machine.gameSpeed(&gameEnd);
        Machine.update(app, newGrid);

        // end early
        gameEnd++;
        if (gameEnd > 22)
            gameEnd = 0;
////////////////////////
        //sleep(period);
        //app.processEvents();
        usleep(1000000)

    }
    return app->exec();
}
