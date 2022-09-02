#include "mywidget.h"
#include <QPushButton>
#include <QDebug>

myWidget::myWidget(QWidget *parent)
    : QWidget(parent)
{
    //创建一个按钮
    QPushButton *btn = new QPushButton;
    //btn->show(); //show以顶层的方式弹出窗口控件

    //希望btn对象依赖在myWeight窗口中
    btn->setParent(this);

    //显示文本
    btn->setText("第一个按钮");

    //第二种重载的方式创建按钮，按照控件的大小创建窗口
    QPushButton *btn2 = new QPushButton("第二个按钮",this);

    //移动btn2按钮
    //Qt坐标系：左上角为原点，向右为x轴正方向，向下为y轴正方向
    btn2->move(100,100);

    //按钮指定大小
    btn2->resize(100,100);

    //重置窗口大小
    resize(600,400);

    //设置固定的窗口大小
    //setFixedSize(600,400);

    //设置窗口标题
    setWindowTitle("第一个窗口");

    //需求，点击第二个按钮，关闭窗口
    //参数1：信号的发送者，参数2：发送的信号（函数的地址），参数3：信号的接受者，参数4：处理的槽函数（函数的地址）
    //信号：signals，槽：slots
    connect(btn2, &QPushButton::clicked, this, &myWidget::close);

}

myWidget::~myWidget()
{

}
