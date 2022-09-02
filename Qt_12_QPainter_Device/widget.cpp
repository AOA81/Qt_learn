#include "widget.h"
#include "ui_widget.h"
#include <QPixmap>
#include <QPainter>
#include <QImage>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);


//    //Pixmap
//    QPixmap pix(300, 300);
//    pix.fill(Qt::white);
//    //声明画家
//    QPainter painter(&pix);
//    painter.setPen(QPen(Qt::green));
//    painter.drawEllipse(QPoint(150, 150), 100, 100);
//    pix.save("/home/aoa/Documents/Qt_learn/Qt_11_QPainter_drawPicture/pix.png");



    //QImage   可以对每个像素进行访问
    QImage img(300, 300, QImage::Format_RGB32);
    img.fill(Qt::white);
    //声明画家
    QPainter painter(&img);
    painter.setPen(QPen(Qt::green));
    painter.drawEllipse(QPoint(150, 150), 100, 100);
    img.save("/home/aoa/Documents/Qt_learn/Qt_11_QPainter_drawPicture/img.png");


}

Widget::~Widget()
{
    delete ui;
}
