#include "widget.h"
#include "ui_widget.h"
#include <QTimer>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    id1 = startTimer(1000);// 调用间隔，单位ms

    id2 = startTimer(2000);

    //第二种定时器方式
    QTimer * timer = new QTimer(this);
    //启动定时器
    timer->start(500);  //单位ms，到了0.5s，该定时器发送一个信号出来

    static int num3 = 0;

    connect(timer, &QTimer::timeout, [=](){
        ui->label_4->setText(QString::number(num3++));
    });

    connect(ui->btn, &QPushButton::clicked, [=](){
       timer->stop();
    });


}

void Widget::timerEvent(QTimerEvent *ev)
{
    static int num;
    static int num2;

    if(ev->timerId() == id1){
    ui->label_2->setText(QString::number(num++));
    }

    if(ev->timerId() == id2){
    ui->label_3->setText(QString::number(num2++));
    }
}

Widget::~Widget()
{
    delete ui;
}
