#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void timerEvent(QTimerEvent *ev);

    int id1; //定时器1
    int id2; //定时器2

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
