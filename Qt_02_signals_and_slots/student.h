#ifndef STUDENT_H
#define STUDENT_H

#include <QObject>

class student : public QObject
{
    Q_OBJECT
public:
    explicit student(QObject *parent = nullptr);

signals:

public slots:
    //槽函数：可以写道public slots下，或public下或全局函数
    //返回值是void，需要声明和实现
    //可以有参数，可以发生重载
    void treat();

    void treat(QString foodName);


};

#endif // STUDENT_H
