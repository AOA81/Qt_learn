#include "mywidget.h"
#include <iostream>
#include <QApplication>  //包含一个应用程序类的头文件
#include <math.h>
#include <QDebug>

using namespace std;

//argc命令行变量的数量，argv命令行变量的数组
int main(int argc, char *argv[])
{
    // a是应用程序对象，Qt中应用程序对象必须有一个，且只能有一个
    QApplication a(argc, argv);

    //实例化一个窗口对象，myweight父类->Qweight
    myWidget w;

    //调用show方法（窗口对象默认不会显示）
    w.show();
    qDebug() << "QDebug Test";
    //w.close();
    //让程序进入消息循环机制
    // 让代码阻塞到这行，后面代码不执行，除非点击“叉子（就窗口退出）”
    return a.exec();


}
