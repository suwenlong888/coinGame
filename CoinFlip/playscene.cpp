#include "playscene.h"
#include "QDebug"
#include <QMenuBar>
#include <QPainter>
#include "mypushbutton.h"
#include <QTimer>
#include <QLabel>
#include <mycoin.h>
#include <dataconfig.h>
#include "QPropertyAnimation"
//PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
//{

//}
PlayScene::PlayScene(int levelnum){
    QString str=QString("进入第%1关").arg(levelnum);
    qDebug()<<str;
    this->levelnum=levelnum;
    this->setFixedSize(320,588);
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    this->setWindowTitle("翻金币场景");
    QMenuBar * bar = menuBar();
    setMenuBar(bar);
    QMenu * startMenu = bar->addMenu("开始");
    QAction *  quitAction = startMenu->addAction("退出");
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });
    MyPushButton * backBtn = new MyPushButton(":/res/BackButton.png" , ":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width() , this->height() - backBtn->height());

    //点击返回
    connect(backBtn,&MyPushButton::clicked,[=](){
        qDebug() << "翻金币场景中：点击了返回按钮";

        QTimer::singleShot(500,this,[=](){
            emit this->chooseSceneBack();
        });

    });
    dataConfig data;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            gameArray[i][j]=data.mData[this->levelnum][i][j];
        }
    }
    QLabel *lab=new QLabel;
    lab->setParent(this);
    QString str1=QString("Level %1").arg(this->levelnum);
    lab->setText(str1);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    lab->setFont(font);
    lab->setGeometry(30, this->height() - 50,120, 50);
    QLabel* winLabel = new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":/res/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
    winLabel->setPixmap(tmpPix);
    winLabel->setParent(this);
    winLabel->move( (this->width() - tmpPix.width())*0.5 , -tmpPix.height());
    for(int i = 0 ; i < 4;i++)
    {
        for(int j = 0 ; j < 4; j++)
        {
           //绘制背景图片
            QLabel* label = new QLabel;
            label->setGeometry(0,0,50,50);
            label->setPixmap(QPixmap(":/res/BoardNode(1).png"));
            label->setParent(this);
            label->move(57 + i*50,200+j*50);
            QString str3;
            if(gameArray[i][j]==1){
                str3=":/res/Coin0001.png";
            }else{
                str3=":/res/Coin0008.png";
            }
            MyCoin * coin = new MyCoin(str3);
            coin->setParent(this);
            coin->move(59 + i*50,208+j*50);
            coin->posX=i;
            coin->posY=j;
            coin->flag=gameArray[i][j];
            coinBtn[i][j] = coin;
            connect(coin,&QPushButton::clicked,[=](){
                for(int i = 0 ; i < 4;i++)
                {
                    for(int j = 0 ; j < 4; j++)
                    {
                        coinBtn[i][j]->isWin=true;
                    }
                }
                coin->changeFlag();
                 gameArray[i][j] = gameArray[i][j] == 0 ? 1 : 0;
                 QTimer::singleShot(300, this,[=](){
                     if(coin->posX+1 <=3)
                     {
                       coinBtn[coin->posX+1][coin->posY]->changeFlag();
                       gameArray[coin->posX+1][coin->posY] = 1- gameArray[coin->posX+1][coin->posY];
                     }
                     if(coin->posX-1>=0)
                     {
                       coinBtn[coin->posX-1][coin->posY]->changeFlag();
                       gameArray[coin->posX-1][coin->posY] = 1-gameArray[coin->posX-1][coin->posY];
                     }
                     if(coin->posY+1<=3)
                     {
                      coinBtn[coin->posX][coin->posY+1]->changeFlag();
                      gameArray[coin->posX][coin->posY+1] = 1- gameArray[coin->posX][coin->posY+1];
                     }
                     if(coin->posY-1>=0)
                     {
                      coinBtn[coin->posX][coin->posY-1]->changeFlag();
                      gameArray[coin->posX][coin->posY-1] = 1-gameArray[coin->posX][coin->posY-1];
                     }
                    this->isWin = true;
                   for(int i = 0 ; i < 4;i++)
                   {
                       for(int j = 0 ; j < 4; j++)
                       {
                           //qDebug() << "gameArray[i][j]";
                           //qDebug() << coinBtn[i][j]->flag <<" "<<gameArray[i][j];
                           if( gameArray[i][j] == 0)
                           {
                               this->isWin = false;
                               //break;
                           }
                       }
                   }
                   for(int i = 0 ; i < 4;i++)
                   {
                       for(int j = 0 ; j < 4; j++)
                       {
                           coinBtn[i][j]->isWin=false;
                       }
                   }
                  if(this->isWin)
                  {
                       qDebug() << "胜利";
                       for(int i = 0 ; i < 4;i++)
                            {
                              for(int j = 0 ; j < 4; j++)
                              {
                                coinBtn[i][j]->isWin = true;
                              }
                      }
                       QPropertyAnimation * animation1 =  new QPropertyAnimation(winLabel,"geometry");
                      animation1->setDuration(1000);
                      animation1->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                      animation1->setEndValue(QRect(winLabel->x(),winLabel->y()+114,winLabel->width(),winLabel->height()));
                      animation1->setEasingCurve(QEasingCurve::OutBounce);
                      animation1->start();
                  }

                 });
            });

        }
    }
}

void PlayScene::paintEvent(QPaintEvent *)
{
    //创建背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap( 10,30,pix.width(),pix.height(),pix);

}
