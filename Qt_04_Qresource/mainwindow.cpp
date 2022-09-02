#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //设置图标
    //ui->actionNew->setIcon(QIcon("/home/aoa/Pictures/Wallpapers/130F6110406-4.jpg"));

    //使用添加Qt资源": + 前缀名 + 文件名"
    //Qt项目里面添加resourcefile
    ui->actionNew->setIcon(QIcon(":/opencv_imgs/OpenCV.png"));
    ui->actionOpen->setIcon(QIcon(":/opencv_imgs/test2.jpg"));

}

MainWindow::~MainWindow()
{
    delete ui;
}
