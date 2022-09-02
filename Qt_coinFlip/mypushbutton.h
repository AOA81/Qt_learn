#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyPushButton(QWidget *parent = nullptr);

    //构造函数，参数1:正常显示的图片，参数2：按下后显示的图片
    MyPushButton(QString normalImg, QString pressImg = "");

    //成员属性，保存用户传入的默认路径
    QString normalImgPath;
    QString pressImgPath;

    //弹跳特效
    void zoom1();  //向下跳
    void zoom2();  //向上跳

    //重写鼠标点击和释放事件
    void mousePressEvent(QMouseEvent * e);
    void mouseReleaseEvent(QMouseEvent * e);

signals:

public slots:
};

#endif // MYPUSHBUTTON_H
