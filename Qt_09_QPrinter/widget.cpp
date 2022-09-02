#include "widget.h"
#include "ui_widget.h"
#include <QPainter>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}


void Widget::paintEvent(QPaintEvent *)
{
    //实例化画家对象，thsi指定的是绘图设备
    QPainter painter(this);

    //设置画笔
    QPen pen(QColor(255, 0, 0));
    //设置画笔宽度
    pen.setWidth(3);
    //设置风格(点划线）
    pen.setStyle(Qt::DashLine);
    //让画家使用这个笔
    painter.setPen(pen);


    //画刷，对于封闭图形填充颜色
    QBrush brush(QColor(0, 255, 0));
    //设置画刷风格
    brush.setStyle(Qt::Dense7Pattern);

    //让画家使用画刷
    painter.setBrush(brush);

    //画线
    painter.drawLine(QPoint(0,0), QPoint(100,100));

    //画圆（圆是一种特殊的椭圆）
    painter.drawEllipse(QPoint(100,100), 50, 50);

    //画一个矩形
    painter.drawRect(QRect(20, 20, 50, 50));

    //画文字
    painter.drawText(QRect(10, 200, 200, 50), "好好学习，天天向上");

}


Widget::~Widget()
{
    delete ui;
}
