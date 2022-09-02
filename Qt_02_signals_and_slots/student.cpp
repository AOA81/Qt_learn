#include "student.h"
#include <QDebug>


student::student(QObject *parent) : QObject(parent)
{

}


void student::treat()
{

    qDebug() << "请老师吃饭";

}


void student::treat(QString foodName)
{

    //QSring转char*类型
    qDebug() << "yaochi:" << foodName.toUtf8().data();


}
