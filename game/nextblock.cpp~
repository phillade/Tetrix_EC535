#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <string.h>

#include <utility> // for pair
#include <vector>
#include <iostream>

using namespace std;

class nextBlock{
    int cellSize;
    QFrame * grid[4][4];
    QFrame nextBlockWidget;
    QGridLayout * nextBlockLayout;
 public:
    nextBlock(){
        cellSize = 11;
        //nextBlockWidget = new QFrame();
        nextBlockLayout = new QGridLayout(&nextBlockWidget);

        nextBlockLayout->setSpacing(0);
        // Create widget for each cell in grid
        for (int i=0; i<4; i++){
            for (int j=0; j<4; j++){
                QFrame * w = new QFrame();
                w->setFixedSize(cellSize, cellSize);
                w->setFrameStyle(QFrame::Box); // NoFrame
                w->setLineWidth(1);
                w->setStyleSheet("background:lightgray;");
                nextBlockLayout->addWidget(w,i,j);
                grid[i][j] = w;
            }
        }
        nextBlockLayout->setSizeConstraint(QLayout::SetFixedSize); // Grid doesn't resize w/ window resize
        nextBlockLayout->setMargin(0); // Distance between widget border and layout border = 0
        nextBlockWidget.setLayout(nextBlockLayout);
        nextBlockWidget.setFrameStyle(QFrame::Box); // set widget border
        nextBlockWidget.setLineWidth(1);
    }

    QFrame * getWidget(){
        return &nextBlockWidget;
    }

    int getCellSize(){
        return cellSize;
    }

    void setCellSize(int i){
        cellSize = i;
    }

    void setCellColor(int rowIdx, int colIdx, string color){
        string colorStr = "background:"+color+";";
        grid[rowIdx][colIdx]->setStyleSheet(QString::fromStdString(colorStr));
    }

    void placeBlock(vector<pair<int, int> > coord, string color){
        for (int i=0; i<4; i++){
            for (int j=0; j<4; j++){
                setCellColor(i, j, "lightgray");
            }
        }

        for (int i=0; i<coord.size(); i++){
            setCellColor(coord[i].first, coord[i].second, color);
        }
    }
};
