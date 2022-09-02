#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QFile>
#include <QTextCodec>
#include <QFileInfo>
#include <QDebug>
#include <QDateTime>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //点击选取文件按钮，弹出对话框
    connect(ui->pushButton, &QPushButton::clicked, [=](){
        QString path = QFileDialog::getOpenFileName(this, "打开文件", "/home/aoa/Videos");
        ui->lineEdit->setText(path);


        //编码格式的类
        //QTextCodec * codec = QTextCodec::codecForName("gbk");


        //读取内容
        //默认支持utf8格式
        QFile file(path);  //参数就是文件的路径
        //设置打开方式
        file.open(QIODevice::ReadOnly);

        //QByteArray array = file.readAll();
        QByteArray array;
        while(!file.atEnd()){
            array += file.readLine(); //按行读
        }

        //读取的数据放入textEdit中
        ui->textEdit->setText(array);

        //转码（gbk->utf8)
        //ui->textEdit->setText(codec->toUnicode(array));

        file.close();


//        //写入操作
//        file.open(QIODevice::Append); //追加的方式进行写
//        file.write("aaaaaaaa");

        file.close();


        //Qfileinfo文件信息类
        QFileInfo info(path);
        qDebug() << "大小" << info.size() << "后缀名" << info.suffix() << "文件名称" << info.fileName() << "路径" << info.filePath();

        qDebug() << "创建日期" << info.created().toString("yyyy/MM/dd hh:mm:ss");

        qDebug() << "修改日期" << info.lastModified().toString(("yyyy-MM-dd hh:mm:ss"));



    });



}

Widget::~Widget()
{
    delete ui;
}
