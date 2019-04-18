#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <string.h>

#include <utility> // for pair
#include <vector>
#include <iostream>

using namespace std;

class Grid{
    int row;
    int col;
    int cellSize;
    QFrame * grid[10][20];
    QFrame * gridWidget;
    QGridLayout * gridLayout;
 public:
    Grid(){
        row = 10;
        col = 20;
        cellSize = 20;
        gridWidget = new QFrame();
        gridLayout = new QGridLayout(gridWidget);

        gridLayout->setSpacing(0);
        // Create widget for each cell in grid
        for (int i=0; i<row; i++){
            for (int j=0; j<col; j++){
                QFrame * w = new QFrame();
                w->setFixedSize(cellSize, cellSize);
                w->setFrameStyle(QFrame::Box); // NoFrame
                w->setLineWidth(1);
                w->setStyleSheet("background:lightgray;");
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

    void setCellColor(int rowIdx, int colIdx, string color){
        string colorStr = "background:"+color+";";
        grid[rowIdx][colIdx]->setStyleSheet(QString::fromStdString(colorStr));
    }

    vector<pair<int, int> > placeBlock(vector<pair<int, int> > coord, pair<int,int> loc, string color){
        int x, y;
        vector<pair<int, int> > newCoord;
        for (int i=0; i<coord.size(); i++){
            x = loc.first + coord[i].first;
            y = loc.second + coord[i].second;
            if (x<0 || y<0)
                continue;
            setCellColor(x, y, color);

            newCoord.push_back(make_pair(x, y));
        }
        return newCoord;
    }

    void replace(vector<pair<int, int> > coord, vector<pair<int, int> > newCoord, string color){
        // Set original coordinates back to gray
        for (int i=0; i<coord.size(); i++){
            if (coord[i].second<0 || coord[i].second>19)
                continue;
            setCellColor(coord[i].first, coord[i].second, "lightgray");
        }

        // Color translated down coordinates
        for (int i=0; i<newCoord.size(); i++){
            if (newCoord[i].second<0 || newCoord[i].second>19)
                continue;
            setCellColor(newCoord[i].first, newCoord[i].second, color);
        }
    }
};


