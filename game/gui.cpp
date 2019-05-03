#include "gui.h"
 
#include <QTextDocument>
#include <QIcon>
#include <QPainter>
#include <QPixmap>
#include <QCoreApplication>

Gui::Gui(QWidget *parent)
    : QMainWindow(parent)
{
	//QGraphicsScene * scene = new QGraphicsScene(this)
    // Create the button, make "this" the parent
    m_button = new QPushButton(this);
    connect(m_button, SIGNAL (released()), this, SLOT (handleButton()));

    QTextDocument Text;
    Text.setHtml("<h2>Hello</h2>");
 
    QPixmap pixmap(Text.size().width(), Text.size().height());
    pixmap.fill( Qt::transparent );
    QPainter painter( &pixmap );
	painter.rotate(90);
    Text.drawContents(&painter, pixmap.rect());
 
    QIcon ButtonIcon(pixmap);
    m_button->setIcon(ButtonIcon);
	m_button->setGeometry(100,100,100,100);
    //m_button->setIconSize(pixmap.rect().size());

}
 
void Gui::handleButton()
{
	m_button->setText("Example");
	//Machine.restart();
}

void Gui::setMachine(game* Mach)
{
	Machine = *Mach;
}

QPushButton * Gui::getButton()
{
	return m_button;
}
