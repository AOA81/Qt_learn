#include "mainscene.h"
#include "ui_mainscene.h"
#include <QPainter>
#include <mypushbutton.h>
#include <QDebug>
#include <QTimer>
#include <QSound>

MainScene::MainScene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainScene)
{
    ui->setupUi(this);

    //配置主场景
    //设置固定大小
    setFixedSize(320, 588);

    //设置图标
    setWindowIcon(QIcon(":/res/Coin0001.png"));

    //设置标题
    setWindowTitle("翻金币_主场景");

    //退出按钮的实现
    connect(ui->actionQuit, &QAction::triggered, this, &MainScene::close);

    //准备开始按钮的音效
    QSound * startSound = new QSound(":/res/TapButtonSound.wav", this);

    //设置开始按钮
    MyPushButton * startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width() * 0.5 - startBtn->width() * 0.5, this->height() * 0.7);  //屏幕宽度的一半减去按钮宽度的一半

    //实例化选择关卡场景
    chooseScene = new ChooseLevelScene;

    //监听选择关卡的返回按钮的自定义信号
    connect(chooseScene, &ChooseLevelScene::chooseSenceBack, this, [=](){
        this->setGeometry(chooseScene->geometry());
        chooseScene->hide();
        this->show();
    });

    connect(startBtn, &MyPushButton::clicked, [=](){
        //播放音效
        startSound->play();

        //做弹起的特效
        startBtn->zoom1();
        startBtn->zoom2();

        //延时进入到下一个场景,0.5s,让当前对象执行匿名函数
        QTimer::singleShot(500, this, [=](){
            //设置位置
            chooseScene->setGeometry(this->geometry());

            //选择进入关卡选择场景
            //自身隐藏
            this->hide();
            //选择关卡场景
            chooseScene->show();
        });
    });
}

void MainScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    //画一个背景上的图标
    pix.load(":/res/Title.png");
    //缩放图片
    pix = pix.scaled(pix.width() * 0.5, pix.height() * 0.5);
    painter.drawPixmap(10, 30, pix);
}

MainScene::~MainScene()
{
    delete ui;
}
