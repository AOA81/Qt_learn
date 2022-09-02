#ifndef TEACHER_H
#define TEACHER_H

#include <QObject>

class Teacher : public QObject
{
    Q_OBJECT
public:
    explicit Teacher(QObject *parent = nullptr);

signals:
    //自定义的信号位置
    //没有返回值（void）
    //只需要声明，不需要实现
    //可以有参数的，可以重载
    void hungry();

    void hungry(QString foodName);

public slots:
};

#endif // TEACHER_H
