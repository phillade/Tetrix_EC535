#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <string.h>

class Grid{
    int row = 20;
    int col = 10;
    int cellSize = 30;
    QFrame * grid[20][10];
    QFrame * gridWidget = new QFrame();
    QGridLayout * gridLayout = new QGridLayout(gridWidget);
 public:
    Grid(){
        gridLayout->setSpacing(0);
        // Create widget for each cell in grid
        for (int i=0; i<row; i++){
            for (int j=0; j<col; j++){
                QFrame * w = new QFrame();
                w->setFixedSize(cellSize, cellSize);
                w->setFrameStyle(QFrame::Box); // NoFrame
                w->setLineWidth(1);
                gridLayout->addWidget(w,i,j);
                grid[i][j] = w;
            }
        }
        gridLayout->setSizeConstraint(QLayout::SetFixedSize); // Grid doesn't resize w/ window resize
        gridLayout->setMargin(0); // Distance between widget border and layout border = 0
        gridWidget->setLayout(gridLayout);
        gridWidget->setFrameStyle(QFrame::Box); // set widget border
        gridWidget->setLineWidth(1);
    }

    QFrame * getWidget(){
        return gridWidget;
    }

    int getCellSize(){
        return cellSize;
    }

    void setCellSize(int i){
        cellSize = i;
    }

    void setCellColor(int rowIdx, int colIdx, std::string color){
        std::string colorStr = "background:"+color+";";
        grid[rowIdx][colIdx]->setStyleSheet(QString::fromStdString(colorStr));
    }
};
