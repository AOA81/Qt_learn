#include "chooselevelscene.h"
#include <QMenuBar>
#include <QPainter>
#include "mypushbutton.h"
#include <QTimer>
#include <QLabel>
#include <QDebug>
#include"playscene.h"
#include <QSound>

ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    //配置选择关卡场景
    this->setFixedSize(320, 588);

    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));

    //设置标题
    this->setWindowTitle("选择关卡场景");

    //利用代码创建菜单栏
    QMenuBar * bar = menuBar();
    setMenuBar(bar);

    //创建开始菜单
    QMenu * startMenu = bar->addMenu("开始");

    //创建退出菜单项
    QAction * quitAction = startMenu->addAction("退出");

    //点击退出实现退出游戏
    connect(quitAction, &QAction::triggered, [=](){
        this->close();
    });

    //准备选择关卡按钮的音效
    QSound * selectSound = new QSound(":/res/TapButtonSound.wav", this);

    //返回按钮
    MyPushButton * backBtn = new MyPushButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");

    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width(), this->height() - backBtn->height());

    connect(backBtn, &MyPushButton::clicked, [=](){
        //延时返回
        QTimer::singleShot(500, this, [=](){
            //告诉主场景，需要返回，主场景需要监听按钮
            emit this->chooseSenceBack();
        });
    });

    //创建选择关卡按钮
    for(int i = 0; i<20; i++)
    {
        MyPushButton * menuBtn = new MyPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(25 + i%4 * 70, 130 + i/4 * 70);

        //监听按钮的点击事件
        connect(menuBtn, &MyPushButton::clicked, [=](){
            selectSound->play();

            QString str = QString("选择了第 %1 关").arg((i + 1));
            //qDebug() << str;

            //进入游戏场景
            this->hide();
            play = new PlayScene(i+1);

            //设置游戏场景的初始位置
            play->setGeometry(this->geometry());

            play->show();

            //监听游戏关卡场景的返回按钮的自定义信号
            connect(play, &PlayScene::chooseSenceBack, this, [=](){
                this->setGeometry(play->geometry());
                this->show();
                delete play;
                play = NULL;
            });
        });

        QLabel * label = new QLabel;
        label->setParent(this);
        label->setFixedSize(menuBtn->width(), menuBtn->height());
        label->setText(QString::number(i+1));
        label->move(25 + i%4 * 70 , 130 + i/4 * 70);

        //设置label上的文字对齐方式，水平居中和垂直居中
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        //设置鼠标进行穿透，不然鼠标点击点到label上了，而不是btn上
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }
}

void ChooseLevelScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    //load background
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    //load title
    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width() - pix.width())*0.5, 30, pix.width(), pix.height(), pix);
}
