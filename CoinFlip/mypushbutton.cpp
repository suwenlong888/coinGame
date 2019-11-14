#include "mypushbutton.h"
#include <QDebug>
#include <QPropertyAnimation>
//MyPushButton::MyPushButton(QWidget *parent) : QPushButton(parent)
//{

//}
MyPushButton::MyPushButton(QString normalImg, QString pressImg ){
     normalImgPath=normalImg;
     pressImgPath=pressImg;
     QPixmap pix;
     bool ret=pix.load(normalImg);
     if(!ret)
     {
        qDebug() << "图片加载失败";
        return;
     }

     this->setFixedSize(pix.width(),pix.height());
     this->setStyleSheet("QPushButton{border:0px;}");
     this->setIcon(pix);
     this->setIconSize(QSize(pix.width(),pix.height()));

}
void MyPushButton::mousePressEvent(QMouseEvent *e){
    if(this->pressImgPath!=""){
        QPixmap pix;
        bool ret=pix.load(this->pressImgPath);
        if(!ret)
        {
           qDebug() << "图片加载失败";
           return;
        }

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    return QPushButton::mousePressEvent(e);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent *e){
    if(this->pressImgPath!=""){
        QPixmap pix;
        bool ret=pix.load(this->normalImgPath);
        if(!ret)
        {
           qDebug() << "图片加载失败";
           return;
        }

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    return QPushButton::mouseReleaseEvent(e);
}
void MyPushButton::zoom1(){
    QPropertyAnimation *pro=new QPropertyAnimation(this,"geometry");
    pro->setDuration(200);
    pro->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    pro->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    pro->setEasingCurve(QEasingCurve::OutBounce);
    pro->start();
}
void MyPushButton::zoom2(){
    QPropertyAnimation *pro=new QPropertyAnimation(this,"geometry");
    pro->setDuration(200);
    pro->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    pro->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    pro->setEasingCurve(QEasingCurve::OutBounce);
    pro->start();
}

