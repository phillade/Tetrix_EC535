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
		score = 0;
        label = new QLabel;
        qmap = new QPixmap(50,70);
        paint = new QPainter(qmap);
        rect = new QRect(-70,0,70,50); // subtract by 90, switch width and height due to rotate

        label->setAlignment(Qt::AlignCenter);
        // Add frame
        //label->setFrameStyle(QFrame::Box);
        //label->setLineWidth(2);
        // Set size
        label->setFixedSize(50,70);
        label->setStyleSheet("QLabel {background-color : black};");
        // Format font
        paint->setFont( QFont("Arial",20) );
        paint->setPen(Qt::white);
        paint->fillRect(*rect, Qt::black);
        // Rotate
        paint->rotate(-90);
        // Draw text
        std::ostringstream ss;
		  ss << score;
        std::string scoreStr = "Score:\n" + ss.str();
        paint->drawText(*rect,Qt::AlignCenter,QString::fromStdString(scoreStr));
        label->setPixmap(*qmap);
    }

    QLabel * getLabel(){
        return label;
    }

    int getScore(){
        return score;
    }

    void setScore(){
		std::ostringstream ss;
		ss << score;
        std::string scoreStr = "Score:\n" + ss.str();
        paint->eraseRect(*rect);
        paint->fillRect(*rect, Qt::black);
        paint->drawText(*rect,Qt::AlignCenter,QString::fromStdString(scoreStr));
        label->setPixmap(*qmap);
    }
        
	void setNewScore(int rowsCleared){
    	//n 	40 * (n + 1) 	100 * (n + 1) 	300 * (n + 1) 	1200 * (n + 1) 
    	int n = rowsCleared + 1;
    	switch (rowsCleared){
    		case 1:
    			score += 40 * n;
    			break;
    		case 2:
    			score += 100 * n;
    			break;
    		case 3:
    			score += 300 * n;
    			break;
    		case 4:
    			score += 1200 * n;
    			break; 
    		default:
    			std::cout << "Rows cleared not 1-4????? " << std::endl;
    	}
    	setScore();    	
    };
};


