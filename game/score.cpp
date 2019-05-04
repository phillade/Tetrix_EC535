/* Score label that shows the current player score */

#include <QLabel>
#include <QPainter>
#include <QPixmap>
#include <string.h>
#include <sstream>

class Score{
    int score;
    QLabel * label;
    QPixmap * qmap;
    QPainter * paint;
    QRect * rect;
 public:
    Score(){
        // Initialize variables
		score = 0; 
        label = new QLabel;
        qmap = new QPixmap(50,70);
        paint = new QPainter(qmap);
        rect = new QRect(-70,0,70,50); // subtract by 90, switch width and height due to rotate
        // center label
        label->setAlignment(Qt::AlignCenter);
        // Set size of label
        label->setFixedSize(50,70);
        label->setStyleSheet("QLabel {background-color : black};");
        // Format font
        paint->setFont( QFont("Arial",20) );
        paint->setPen(Qt::white);
        paint->fillRect(*rect, Qt::black);
        // Rotate 90 degrees
        paint->rotate(-90);
        // Draw text
        std::ostringstream ss;
		  ss << score;
        std::string scoreStr = "Score:\n" + ss.str();
        paint->drawText(*rect,Qt::AlignCenter,QString::fromStdString(scoreStr));
        label->setPixmap(*qmap);
    }

    QLabel * getLabel(){
        /* Get label widget */
        return label;
    }

    int getScore(){
        /* Get score */
        return score;
    }

    void setScore(){
        /* Set score */
		std::ostringstream ss;
		ss << score;
        std::string scoreStr = "Score:\n" + ss.str();
        paint->eraseRect(*rect);
        paint->fillRect(*rect, Qt::black);
        paint->drawText(*rect,Qt::AlignCenter,QString::fromStdString(scoreStr));
        label->setPixmap(*qmap);
    }
        
	void setNewScore(int rowsCleared){
    	/* Update score */
    	int n = rowsCleared + 1;
    	switch (rowsCleared){
		case 0:
			score = 0;
			break;
    		case 1:
    			score += 100;
    			break;
    		case 2:
    			score += 250;
    			break;
    		case 3:
    			score += 400;
    			break;
    		case 4:
    			score += 1000;
    			break; 
    		default:
    			std::cout << "Rows cleared not 1-4????? " << std::endl;
    	}
    	setScore();    	
    };
};


