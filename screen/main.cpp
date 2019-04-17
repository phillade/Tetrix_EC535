#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <iostream>
//#include <QTest>
#include <unistd.h>

#include "grid.cpp"
#include "score.cpp"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    /////////// Create Grid ////////////
    Grid newGrid;
    QFrame * gridWidget = newGrid.getWidget();

    ///////////// Add score box /////////////
    Score newScore;
    QLabel * scoreLabel = newScore.getLabel();

    ////////// Create main widget (widget that is displayed) /////////////////
    QWidget * main = new QWidget();
	 main->setAutoFillBackground(true);
    // Layout
    QHBoxLayout* centralLayout = new QHBoxLayout();
    // Add widgets to layout
    centralLayout->addWidget(gridWidget);
    centralLayout->addWidget(scoreLabel);
    // Add layout to main widget
    main->setLayout(centralLayout);

    main->showFullScreen();

    /* Testing */
    // Loop through some color changes on grid
    for (int i=0; i<5; i++){
        newGrid.setCellColor(0,i,"red");
        newScore.setScore(i+1);
        //w.update();
        app.processEvents();
        //QTest::qSleep(500);
        usleep(1000000);
    }

    return app.exec();
}