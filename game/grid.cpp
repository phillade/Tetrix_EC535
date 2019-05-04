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
        /* Grid constructor */
        // Set grid size
        row = 10;
        col = 20;
        // Set cell size
        cellSize = 16;
        // Create widget
        gridWidget = new QFrame();
        // Create layout for widget
        gridLayout = new QGridLayout(gridWidget);
        gridLayout->setSpacing(0);

        // Create widget for each cell in grid
        for (int i=0; i<row; i++){
            for (int j=0; j<col; j++){
                QFrame * w = new QFrame();
                w->setFixedSize(cellSize, cellSize);
                w->setFrameStyle(QFrame::Box); // No frame
                w->setLineWidth(1); 
                w->setStyleSheet("background:lightgray;"); // set background color
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
        /* 
        Get grid widget 
        
        ARGS: 
            void

        RETURNS:
            gridWdiget (QFrame*): QFrame object holding QFrame cells in layout
        */
        return gridWidget;
    }

    void setCellColor(int rowIdx, int colIdx, string color){
        /* 
        Set cell color 
    
        ARGS:
            rowIdx (int): row index of cell coordinate
            colIdx (int): col index of cell coordinate
            color (string): color to set cell to

        RETURN:
            void
        */
        string colorStr = "background:"+color+";";
        grid[rowIdx][colIdx]->setStyleSheet(QString::fromStdString(colorStr));
    }

    void placeBlock(vector<pair<int, int> > coord, string color){
        /* 
            Place a block on the grid

            coord (vector<pair<int, int> >): coordinates of block to place
            color (string): color to set block to on grid
        */
        for (int i=0; i<coord.size(); i++){
            if (coord[i].first<0 || coord[i].second<0) // skip if not in grid range
                continue;
            setCellColor(coord[i].first, coord[i].second, color);
        }
    }

    void replaceBlock(vector<pair<int, int> > coord, vector<pair<int, int> > newCoord, string color){
        /* 
            Replace block with new block 
        
            coord (vector<pair<int, int> >): old coordinates to replace
            newCoord (vector<pair<int, int> >): coordinates to replace old coordinates w/
            color (string): color for new block to be

        */
        
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


