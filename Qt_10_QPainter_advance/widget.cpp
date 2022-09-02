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
    //画家高级设置
    QPainter painter(this);

    //画园
    painter.drawEllipse(QPoint(100,50), 50, 50);
    //设置抗锯齿(降低效率）
    painter.setRenderHint(QPainter::HighQualityAntialiasing);
    painter.drawEllipse(QPoint(200,50), 50, 50);

    //矩形
    painter.drawRect(QRect(20, 20, 50, 50));
    //让画家移动指定向量
    painter.translate(100,0);

    //保存画家状态
    painter.save();
    painter.drawRect(QRect(20, 20, 50, 50));
    painter.translate(100, 0);
    painter.restore();//还原的状态就是保存的状态位置
    painter.drawRect(QRect(20, 20, 50, 50));

}

Widget::~Widget()
{
    delete ui;
}
