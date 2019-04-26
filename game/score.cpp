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
        qmap = new QPixmap(70,90);
        paint = new QPainter(qmap);
        rect = new QRect(-90,0,90,70); // translate by 90, switch width and height due to rotate

        label->setAlignment(Qt::AlignCenter);
        // Add frame
        //label->setFrameStyle(QFrame::Box);
        //label->setLineWidth(2);
        // Set size
        label->setFixedSize(70,90);
        label->setStyleSheet("QLabel {background-color : gray};");
        // Format font
        paint->setFont( QFont("Arial",24) );
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

    void calculateScore(int lines, int level){
        switch(lines){
            case 1:
                score = level+1;
                score = 40*score;
                break;
            case 2:
                score = level+1;
                score = 100*score;
                break;
            case 3:
                score = level+1;
                score = 300*score;
                break;
            case 4:
                score = level+1;
                score = 1200*score;
                break;
        }
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


