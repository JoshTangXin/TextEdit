#include "mylabel.h"
#include <QMouseEvent>
#include "mainwindow.h"

mylabel::mylabel(QWidget *parent)
{
//    this->setText("www.baidu.com");

//    this->show();
}


void mylabel::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        emit label_Clicked();
    }
    else
    {
        QLabel::mousePressEvent(event);
    }

}

