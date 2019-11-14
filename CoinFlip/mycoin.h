#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyCoin(QWidget *parent = nullptr);
    MyCoin(QString btnImg);
    void mousePressEvent(QMouseEvent *e);
    int posX; //x坐标
    int posY; //y坐标
    bool flag; //正反标志
    void changeFlag();
    QTimer*timer1;
    QTimer*timer2;
    int min=1;
    int max=8;
    bool isAnimation  = false;
    bool isWin = false;
signals:

public slots:
};

#endif // MYCOIN_H
