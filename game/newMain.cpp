#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTimer>
#include <iostream>
//#include <QTest>
#include <unistd.h>

//#include "grid.cpp"
#include "score.cpp"

#include "game.h"
#include "block.h"
#include <ctime>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>

int trigger = 0;
game Machine;

void sighandler(int);

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

	//Button stuff
	int pFile, oflags;
	int rd;

	struct sigaction action;
	char buffer[10] = "";

	// Opens to device file
	pFile = open("/dev/tetrix", O_RDWR);
	if (pFile < 0) {
		fprintf (stderr, "tetrix module isn't loaded\n");
		return 1;
	}

	// Setup signal handler
	memset(&action, 0, sizeof(action));
	action.sa_handler = sighandler;
	action.sa_flags = SA_SIGINFO;
	sigemptyset(&action.sa_mask);
	sigaction(SIGIO, &action, NULL);
	fcntl(pFile, F_SETOWN, getpid());
	oflags = fcntl(pFile, F_GETFL);
	fcntl(pFile, F_SETFL, oflags | FASYNC);

    /////////////////////////////////////////////////////////////////////
    ///////////////////////////// Gameplay //////////////////////////////
    /////////////////////////////////////////////////////////////////////

    std::cout << "Hello, World!" << std::endl;
    //generate a random block
    block thisNewblock = block();

    cout << "The type of block is " << thisNewblock.type << endl;

    int gameEnd = 1;
    srand(time(NULL));

    //intialize a game object
    Machine = game();

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
		usleep(1000000);

		if(trigger){
			rd = read(pFile, buffer, 10);
			buffer[rd] = '\0';
			//printf("%s\n", buffer);
			if(!strcmp(buffer,"one")){
				Machine.update(app, newGrid, true);			
			}
			trigger = 0;
			close(pFile);
			pFile = open("/dev/tetrix", O_RDWR);
			fcntl(pFile, F_SETOWN, getpid());
			oflags = fcntl(pFile, F_GETFL);
			fcntl(pFile, F_SETFL, oflags | FASYNC);
		}
   	}
	close(pFile);
	return app->exec();
}

void sighandler(int signo)
{
	trigger = 1;
}
