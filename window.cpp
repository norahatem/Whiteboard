#include "window.h"

#include <QPainter>
#include <QDebug>
#include <QTextStream>
#include <QMessageBox>

#include <map>
#include <vector>

using namespace std;

Window::Window(QWidget *parent) : QWidget(parent)
{
    // set form size
    setFixedSize(600,600);
}


void Window::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);
    QPen pen;
    QFont font;
    font.setPixelSize(30);
    pen.setWidth(4);
    painter.setPen(pen);
    painter.setFont(font);

}

void Window::mouseReleaseEvent(QMouseEvent * event)
{
    // get click position
    qDebug() << "Mouse x " << event->x() << " Mouse y " << event->y();
}
