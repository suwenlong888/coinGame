#include "chooselevelscene.h"
#include "QMenuBar"
#include "QPainter"
#include <mypushbutton.h>
#include "QTimer"
#include "QLabel"
#include "QTimer"
#include "QDebug"
ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    setFixedSize(320,570);
    setWindowTitle("选关");
    setWindowIcon(QIcon(":/res/Coin0001.png"));
    QMenuBar *bar=menuBar();
    bar->setParent(this);
    QMenu *men=bar->addMenu("开始");
    QAction*act=men->addAction("结束");
    connect(act,&QAction::triggered,[=](){
        this->close();
    });
    MyPushButton *btn=new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    btn->setParent(this);
    btn->move(this->width()-btn->width(),this->height()-btn->height());
    connect(btn,&QPushButton::clicked,[=](){
        QTimer::singleShot(500,this,[=](){
           emit this->selectmainback();
        });
    });
    for( int i = 0 ; i < 20 ;i ++)
    {
        MyPushButton * menuBtn = new MyPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move( 25 + i%4 * 70 , 130 + i/4 * 70  );

        //监听每个按钮的点击事件
        connect(menuBtn,&MyPushButton::clicked,[=](){
            QString str = QString("您选择的是第 %1 关 ").arg( i + 1);
            qDebug() <<str;
            this->hide();
            play=new PlayScene(i+1);
            play->show();
            connect(play,&PlayScene::chooseSceneBack,[=](){
                this->show();
                delete play;
                play=NULL;
            });

        });

        QLabel * label = new QLabel;
        label->setParent(this);
        label->setFixedSize(menuBtn->width(),menuBtn->height());
        label->setText(QString::number(i+1));
        label->move(25 + i%4 * 70 , 130 + i/4 * 70 );

        //设置 label上的文字对齐方式 水平居中和 垂直居中
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        //设置让鼠标进行穿透   51号属性
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }

}
void ChooseLevelScene::paintEvent(QPaintEvent *event){
    QPainter penter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    penter.drawPixmap(0,0,pix);
    pix.load(":/res/Title.png");
    pix.scaled(pix.width()*0.5,pix.height()*0.5);
    penter.drawPixmap(10,30,pix.width(),pix.height(),pix);
}
