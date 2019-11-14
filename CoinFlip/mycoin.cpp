#include "mycoin.h"
#include "QDebug"
#include "QTimer"
//MyCoin::MyCoin(QWidget *parent) : QWidget(parent)
//{

//}
MyCoin::MyCoin(QString btnImg){
    QPixmap pix;
    bool ret=pix.load(btnImg);
    if(!ret){
        QString str=QString("图片%1 fail").arg(btnImg);
        qDebug()<<str;
    }
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));
    this->timer1=new QTimer;
    this->timer2=new QTimer;
    connect(timer1,&QTimer::timeout,[=](){
            QPixmap pixmap;
            QString str = QString(":/res/Coin000%1.png").arg(this->min++);
            pixmap.load(str);
            this->setFixedSize(pixmap.width(),pixmap.height() );
            this->setStyleSheet("QPushButton{border:0px;}");
            this->setIcon(pixmap);
            this->setIconSize(QSize(pixmap.width(),pixmap.height()));
            if(this->min > this->max) //如果大于最大值，重置最小值，并停止定时器
            {
                this->min = 1;
                this->isAnimation  = false;
                timer1->stop();
            }
        });
    connect(timer2,&QTimer::timeout,[=](){
            QPixmap pixmap;
            QString str = QString(":/res/Coin000%1.png").arg(this->max--);
            pixmap.load(str);
            this->setFixedSize(pixmap.width(),pixmap.height() );
            this->setStyleSheet("QPushButton{border:0px;}");
            this->setIcon(pixmap);
            this->setIconSize(QSize(pixmap.width(),pixmap.height()));
            if(this->max < this->min) //如果大于最大值，重置最小值，并停止定时器
            {
                this->max = 8;
                this->isAnimation  = false;
                timer2->stop();
            }
        });
}
void MyCoin::mousePressEvent(QMouseEvent *e)
{
    if(this->isAnimation || this->isWin)
    {
        return;
    }
    else
    {
        return QPushButton::mousePressEvent(e);
    }
}
void MyCoin::changeFlag(){
    if(this->flag){
        timer1->start(30);
        this->isAnimation  = true;
        flag=false;
    }else{
        timer2->start(30);
        this->isAnimation  = true;
        flag=true;
    }
}
