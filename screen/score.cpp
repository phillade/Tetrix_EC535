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
        qmap = new QPixmap(40,60);
        paint = new QPainter(qmap);
        rect = new QRect(-60,-5,60,50);

        label->setAlignment(Qt::AlignCenter);
        // Add frame
        //label->setFrameStyle(QFrame::Box);
        //label->setLineWidth(2);
        // Set size
        label->setFixedSize(40,60);
        label->setStyleSheet("QLabel {background-color : gray};");
        // Format font
        paint->setFont( QFont("Arial",8) );
        paint->setPen(Qt::black);
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

    void setScore(int newScore){
	score = newScore;
	std::ostringstream ss;
	ss << newScore;
        std::string scoreStr = "Score:\n" + ss.str();
        paint->eraseRect(*rect);
        paint->fillRect(*rect, Qt::gray);
        paint->drawText(*rect,Qt::AlignCenter,QString::fromStdString(scoreStr));
        label->setPixmap(*qmap);
    }
};


