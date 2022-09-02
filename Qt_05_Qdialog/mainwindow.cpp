#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include <QColorDialog>
#include <QFileDialog>
#include <QFontDialog>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //点击新建按钮弹出对话框
    connect(ui->actionNew, &QAction::triggered, [=](){
     //对话框分类
     //模态对话框（打开该对话框后，不可以对其他对话框进行操作）    非模态对话框（可以对其他对话框进行操作）

     //创建一个模态对话框
//     QDialog dlg(this);
//     dlg.resize(200,100);
//     dlg.exec();  //带阻塞功能，关闭后继续执行下面的代码
//     qDebug() << "yes";


     //创建一个非模态对话框
//      QDialog dlg2(this);
//      dlg2.resize(200,100);
//      dlg2.show();
//      dlg2.exec();

      //创建一个堆区的非模态dlg也能保证在匿名函数执行完成之后不直接释放
//       QDialog * dlg3 = new QDialog(this);
//       dlg3->resize(200,100);
//       dlg3->show();
//       dlg3->setAttribute(Qt::WA_DeleteOnClose);  //如果不加此行，新建的对话框只有在整个程序结束后才释放内存，但我们希望我们关闭对话框的时候就给释放掉


        //消息对话框
        //QMessageBox::critical(this, "critical", "错误");
        //QMessageBox::information(this, "infor", "信息");

        //有选项的（按钮）可以自定义,第五个参数是默认关联回车的按键, 返回的是按钮的类型（适用于所有消息对话框类型）
//        if (QMessageBox::Cancel == QMessageBox::question(this, "question", "提问", QMessageBox::Cancel | QMessageBox::Save, QMessageBox::Cancel))
//        {
//            qDebug() << "cancel";
//        }
//        else
//        {
//            qDebug() << "save";
//        }

        //QMessageBox::warning(this, "warning", "警告");



        //其他标准对话框
        //颜色对话框(返回值就是一个颜色QColor)
//        QColor color = QColorDialog::getColor(QColor(255,0,0));
//        qDebug() << color.green();

        //文件对话框
        //打开文件,参数1：父亲；参数2：标题；参数3：默认打开路径；参数4：过滤文件格式；返回值：打开的文件具体路径
//        QString str = QFileDialog::getOpenFileName(this, "打开文件", "/", "*.txt");
//        qDebug() << str;

        //字体对话框
        bool flag;
        QFont font = QFontDialog::getFont(&flag, QFont("华文彩云", 36));
        qDebug() << "字体" << font.family().toUtf8().data() << "字号" << font.pointSize() << "是否加粗" << font.bold() << "是否倾斜" << font.italic();



    });





}

MainWindow::~MainWindow()
{
    delete ui;
}
