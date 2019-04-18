#include <QLabel>
#include <QPainter>
#include <QPixmap>
#include <string.h>

class Score{
    int score = 0;
    QLabel * label;
    QPixmap * qmap;
    QPainter * paint;
    QRect * rect;
 public:
    Score(){
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
        std::string scoreStr = "Score:\n" + std::to_string(score);
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
        std::string scoreStr = "Score:\n" + std::to_string(newScore);
        paint->eraseRect(*rect);
        paint->fillRect(*rect, Qt::gray);
        paint->drawText(*rect,Qt::AlignCenter,QString::fromStdString(scoreStr));
        label->setPixmap(*qmap);
    }
};


