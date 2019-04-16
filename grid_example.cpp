#include <QApplication>
#include <QWidget>
#include <QPalette>
#include <QMainWindow>
#include <QLabel>
#include <QHBoxLayout>
#include <QFont>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <iostream>
#include <QTest>

#include "grid.cpp"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    /////////// Create Grid ////////////
    Grid newGrid;
    QFrame * gridWidget = newGrid.getWidget();

    ///////////// Add score box //////////////
    QLabel *label = new QLabel;
    label->setAlignment(Qt::AlignCenter);
    // Label font
    QFont font = label->font();
    font.setPointSize(10);
    label->setFont(font);
    // Add frame
    label->setFrameStyle(QFrame::Box);
    label->setLineWidth(2);
    //label->setStyleSheet("QLabel {background-color : red; color : blue;};");
    // Set text
    label->setText("Score:\n0");
    // Set frame size
    label->setFixedSize(100,40);

    ////////// Create main widget (widget that is displayed) /////////////////
    QWidget * main = new QWidget();
    // Layout
    QHBoxLayout* centralLayout = new QHBoxLayout();
    // Add widgets to layout
    centralLayout->addWidget(gridWidget);
    centralLayout->addWidget(label);
    // Add layout to main widget
    main->setLayout(centralLayout);
    main->show();

    // Loop through some color changes on grid
    for (int i=0; i<5; i++){
        newGrid.setCellColor(0,i,"red");
        //w.update();
        app.processEvents();
        QTest::qSleep(500);
    }

    return app.exec();
}
