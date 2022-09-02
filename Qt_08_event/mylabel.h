#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>

class myLabel : public QLabel
{
    Q_OBJECT
public:
    explicit myLabel(QWidget *parent = nullptr);

    void enterEvent(QEvent * event);

    void leaveEvent(QEvent *);

    void mouseMoveEvent(QMouseEvent *ev);

    void mousePressEvent(QMouseEvent *ev);

    void mouseReleaseEvent(QMouseEvent *ev);


signals:

public slots:
};

#endif // MYLABEL_H
