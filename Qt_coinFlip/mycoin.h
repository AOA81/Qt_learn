#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include <QTimer>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    //参数代表传入的是金币路径还是银币路径
    MyCoin(QString btnImg);

    //金币的属性
    int posX;
    int posY;
    bool flag;

    //改变标志的方法
    void changeFlag();

    QTimer * timer1;
    QTimer * timer2;

    int min = 1;
    int max = 8;

    //正在执行动画的标志
    bool isAnimation = false;

    //重写按下状态
    void mousePressEvent(QMouseEvent * e);

    //判断是否胜利
    bool isWin = false;

signals:

public slots:
};

#endif // MYCOIN_H
