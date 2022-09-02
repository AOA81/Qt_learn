#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include "playscene.h"

class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);

    //重写paint事件
    void paintEvent(QPaintEvent *);

    //申明一个游戏场景指针
    PlayScene * play = NULL;

signals:
    //自定义一个信号，告诉主场景返回按钮的情况
    void chooseSenceBack();

public slots:
};

#endif // CHOOSELEVELSCENE_H
