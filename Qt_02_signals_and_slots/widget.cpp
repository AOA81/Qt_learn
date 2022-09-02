#include "widget.h"
#include "ui_widget.h"
#include <QPushButton>
#include <QDebug>


//Teacher类 老师类
//Student类 学生类
//下课后，老师会触发一个信号，饿了，学生相应信号，请客吃饭

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //创建一个老师的对象
    this->zt = new Teacher(this);

    //创建一个学生的对象
    this->st = new student(this);


//    connect(zt, &Teacher::hungry, st, &student::treat);
//    class_is_over();

    //带参数的连接（发生重载后需要明确哪一个
    //指针指向函数地址
    //函数指针指向函数地址
    void(Teacher::*teacherSingnal)(QString) = &Teacher::hungry;
    void(student::*studentSlot)(QString) = &student::treat;

    //连接
    connect(zt, teacherSingnal, st, studentSlot);
    class_is_over();

    //点击一个按钮触发下课
    QPushButton * btn = new QPushButton("xiake", this);
    //重置窗口大小
    this->resize(600,400);


    //连接
    //connect(btn, &QPushButton::clicked, this, &Widget::class_is_over);

    //无参版本
    void(Teacher::*teacherSingnal2)() = &Teacher::hungry;
    void(student::*studentSlot2)() = &student::treat;
    connect(zt, teacherSingnal2, st, studentSlot2);

    //信号连接信号
    connect(btn, &QPushButton::clicked,zt, teacherSingnal2);

    //断开信号
    disconnect(zt, teacherSingnal2, st, studentSlot2);

    //拓展
    //1. 信号可以连接信号
    //2. 一个信号可以连接多个槽函数
    //3. 多个信号可以连接同一个槽函数
    //4. 信号和槽函数的参数必须一一对应
    //5. 信号和槽的参数个数不一定一致：信号参数的个数可以  多于槽函数的参数个数



    //QT4的信号和槽（不推荐）
    connect(zt, SIGNAL(hungry(QString)), st, SLOT(treat(QString)));
    //优点：参数直观
    //缺点：类型不做检测（例如信号参数少于槽函数编译时不会报错，运行时报错）
    //QT4版本本质为传入一个string类


    //lambda表达式，匿名函数:[=]值传递，[&]引用传递，（）参数，{}实现体，mutable修饰值传递，修改拷贝的数据，不改变本体
    //[]()->int{}表明返回值类型
    [=](){
    btn->setText("aaaa");}();

    connect(btn, &QPushButton::clicked, btn, &QPushButton::close);

    int ret = []()->int{return 1000;}(); //最后一个小括号是函数的调用
    qDebug() << ret;

    QPushButton *btn3 = new QPushButton;
    btn3->setParent(this);
    btn3->setText("close");
    btn3->move(100,0);
    connect(btn3, &QPushButton::clicked, this, [=](){
        //this->close();
        zt->hungry("sdfdfd");
    });


    int m = 10;
    connect(btn3, &QPushButton::clicked, this, [m]()mutable{m=m+10;qDebug()<<m;});

    connect(btn3, &QPushButton::clicked, this, [=](){
        btn3->setText(("sasdfd"));
    });


}

void Widget::class_is_over()
{
    //emit zt->hungry();

    emit zt->hungry("gongbaojiding");
}



Widget::~Widget()
{
    delete ui;
}
