#include "playscene.h"
#include <QMenuBar>
#include <QPainter>
#include "mypushbutton.h"
#include <QTimer>
#include <QLabel>
#include "mycoin.h"
#include "dataconfig.h"
#include <QDebug>
#include <QPropertyAnimation>
#include <QSound>

PlayScene::PlayScene(int levelNum)
{
    this->levelIndex = levelNum;

    //初始化游戏场景
    //设置固定大小
    this->setFixedSize(320, 588);
    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置标题
    this->setWindowTitle("翻金币场景");
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

    //翻金币的音效和胜利的音效
    QSound * flipSound = new QSound(":/res/ConFlipSound.wav", this);
    QSound * winSound = new QSound(":/res/LevelWinSound.wav", this);

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

    //显示当前关卡
    QLabel * label = new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("华文新魏");  //Linux没有这个
    font.setPointSize(20);
    QString str1 = QString("Level: %1").arg(this->levelIndex);
    //将字体设置到标签控件中
    label->setFont(font);
    label->setText(str1);
    label->setGeometry(30, this->height() - 50, 120, 50);

    dataConfig config;
    //初始化每个关卡的二维数组
    for(int i = 0; i<4; i++)
    {
        for(int j = 0; j<4; j++)
        {
            this->gameArray[i][j] = config.mData[this->levelIndex][i][j];
        }
    }

    //胜利图片的显示（预加载）
    QLabel * winLabel = new QLabel;
    QPixmap temPix;
    temPix.load(":/res/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0, 0, temPix.width(), temPix.height());
    winLabel->setPixmap(temPix);
    winLabel->setParent(this);
    winLabel->move((this->width() - temPix.width())*0.5, -temPix.height());

    for(int i = 0; i<4; i++)
    {
        for(int j = 0; j<4; j++)
        {
            //设置金币背景图
            QPixmap pix = QPixmap(":/res/BoardNode.png");
            QLabel * label = new QLabel;
            label->setGeometry(0, 0, pix.width(), pix.height());
            label->setPixmap(pix);
            label->setParent(this);
            label->move(57 + i*pix.width(), 200 + j*pix.height());

            //创建金币
            QString str;
            if(this->gameArray[i][j] == 1)
            {
                str = ":/res/Coin0001.png";
            }
            else {
                str = ":/res/Coin0008.png";
            }

            MyCoin * coin = new MyCoin(str);
            coin->setParent(this);
            coin->move(59 + i*pix.width(), 204 + j*pix.height());

            //给金币的属性赋值
            coin->posX = i;
            coin->posY = j;
            coin->flag = this->gameArray[i][j]; //1正面，0反面
            qDebug() << i << j << coin->flag;

            //将金币放入金币的二维数组中，以方便后期维护
            coinBtn[i][j] = coin;

            //翻转
            connect(coin, &MyCoin::clicked, [=](){
                flipSound->play();

                //在翻转金币的时候禁用其他按钮
                for(int i = 0 ; i < 4; i++)
                {
                    for(int j = 0 ; j < 4 ; j++)
                    {
                        this->coinBtn[i][j]->isWin = true;
                    }
                }

               coin->changeFlag();  //自己翻转
               this->gameArray[i][j] = this->gameArray[i][j] == 0 ? 1 : 0;

               //延时翻转周围
               QTimer::singleShot(300, this, [=](){
                   //翻转右侧
                   if(coin->posX + 1 <= 3) //右侧能翻
                   {
                       coinBtn[coin->posX+1][coin->posY]->changeFlag();
                       this->gameArray[coin->posX+1][coin->posY] = this->gameArray[coin->posX+1][coin->posY] == 0 ? 1 : 0;
                   }

                   //翻转左侧
                   if(coin->posX - 1 >= 0)
                   {
                       coinBtn[coin->posX-1][coin->posY]->changeFlag();
                       this->gameArray[coin->posX-1][coin->posY] = this->gameArray[coin->posX-1][coin->posY] == 0 ? 1 : 0;
                   }

                   //翻转上面
                   if(coin->posY + 1 <= 3)
                   {
                       coinBtn[coin->posX][coin->posY+1]->changeFlag();
                       this->gameArray[coin->posX][coin->posY+1] = this->gameArray[coin->posX][coin->posY+1] == 0 ? 1 : 0;
                   }

                   //翻转下面
                   if(coin->posY - 1 >= 0)
                   {
                       coinBtn[coin->posX][coin->posY-1]->changeFlag();
                       this->gameArray[coin->posX][coin->posY-1] = this->gameArray[coin->posX][coin->posY-1] == 0 ? 1 : 0;
                   }

                   //在翻转完金币的时候释放其他按钮
                   for(int i = 0 ; i < 4; i++)
                   {
                       for(int j = 0 ; j < 4 ; j++)
                       {
                           this->coinBtn[i][j]->isWin = false;
                       }
                   }


                   /*
                    现在是2022年8月31日,下午16点40分
                    有个BUG没找到
                    不想找了
                    留给下次有兴趣的时候
                    估计是不会找了
                    学了小半个月的QT
                    感谢张涛老师
                    对了,那个bug让coin->flag的正负有点问题


                    耶耶耶
                    我找到啦啦啦啦啦啦
                    现在是2022年8月31日17：06
                    我大括号打错了，把判断游戏结束的写到翻转周围按钮的匿名函数外面了
                    我是**
                    */

                   //判断是否胜利
                   this->isWin = true;
                   for(int i = 0; i<4; i++)
                   {
                       for(int j = 0; j<4; j++)
                       {
                           //qDebug() << i << j << coinBtn[i][j]->flag;
                           if(coinBtn[i][j]->flag == false)
                           {
                               this->isWin = false;
                               break;
                           }
                       }
                   }
                   if(this->isWin == true)
                   {
                       winSound->play();
                       qDebug() << "win";
                        //将所有按钮的胜利标志改为ture
                       for(int i = 0; i<4; i++)
                       {
                           for(int j = 0; j<4; j++)
                           {
                               coinBtn[i][j]->isWin = true;
                           }
                       }

                       //将胜利的图片砸下来
                       QPropertyAnimation * animation = new QPropertyAnimation(winLabel, "geometry");
                       //设置时间间隔
                       animation->setDuration(1000);
                       //设置开始位置
                       animation->setStartValue(QRect(winLabel->x(), winLabel->y(), winLabel->width(), winLabel->height()));
                       //设置结束位置
                       animation->setEndValue(QRect(winLabel->x(), winLabel->y()+114, winLabel->width(), winLabel->height()));
                       //设置缓和曲线
                       animation->setEasingCurve(QEasingCurve::OutBounce);
                       //开始
                       animation->start();
                   }
               });
            });
        }
    }
}

void PlayScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    //load background
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    //load title
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width() * 0.5, pix.height() * 0.5);
    painter.drawPixmap(10, 30, pix.width(), pix.height(), pix);
}
