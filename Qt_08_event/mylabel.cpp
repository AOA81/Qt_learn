#include "mylabel.h"
#include <QDebug>
#include <QMouseEvent>

myLabel::myLabel(QWidget *parent) : QLabel(parent)
{
    //设置鼠标追踪
    setMouseTracking(true);

}


void myLabel::enterEvent(QEvent *event)
{
    qDebug() << "enter";

}

void myLabel::leaveEvent(QEvent *)
{
    qDebug() << "leave";
}

void myLabel::mouseMoveEvent(QMouseEvent *ev)
{
//    if(ev->buttons() & Qt::LeftButton){
    qDebug() << "move";
//    }

}

void myLabel::mousePressEvent(QMouseEvent *ev)
{
    //global是基于整个屏幕的坐标系
    if(ev->button() == Qt::LeftButton){
    QString str = QString("press, x = %1, y = %2").arg(ev->x()).arg(ev->y());
    qDebug() << str;
    }


}

void myLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    qDebug() << "release";

}
