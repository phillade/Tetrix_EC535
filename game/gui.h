#ifndef GUI_H
#define GUI_H 

#include <QMainWindow>
#include <QPushButton>
#include "game.h"
 
class Gui : public QMainWindow
{
   Q_OBJECT
public:
	explicit Gui(QWidget *parent = 0);
	QPushButton * getButton();
	void setMachine(game* Mach);
private slots:
   void handleButton();
private:
	QPushButton *m_button;
	game Machine;
};


#endif
