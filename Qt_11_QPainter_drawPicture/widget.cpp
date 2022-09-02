#include "widget.h"
#include "ui_widget.h"
#include <QPainter>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //点击按钮，图片移动
    connect(ui->pushButton, &QPushButton::clicked, [=](){
        //如果手动调用绘图时间，用update更新
        update();

    });

}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    posX += 20;

    //如果超出屏幕，从0开始
    if(posX > this->width())
    {
        posX = 0;
    }

    painter.drawPixmap(posX, 0, QPixmap(":/opencv_imgs/lena.jpg"));
}

Widget::~Widget()
{
    delete ui;
}
