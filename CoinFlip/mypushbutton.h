#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyPushButton(QWidget *parent = nullptr);
    MyPushButton(QString normalImg, QString pressImg = "" );
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

    QString normalImgPath;
    QString pressImgPath;
    void zoom1();
    void zoom2();
signals:

public slots:
};

#endif // MYPUSHBUTTON_H