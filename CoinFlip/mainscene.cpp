#include "mainscene.h"
#include "ui_mainscene.h"
#include "QPainter"
#include "mypushbutton.h"
#include <QDebug>
#include "QTimer"
MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);
    this->setFixedSize(320,588);
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));
    this->setWindowTitle("swl金币反转");
    connect(ui->actionjieshu,&QAction::triggered,[=](){
        this->close();
    });
    MyPushButton *btn=new MyPushButton(":/res/MenuSceneStartButton.png");
    btn->setParent(this);
    btn->move(this->width() * 0.5 - btn->width() * 0.5,this->height()*0.7);
    lev=new ChooseLevelScene;
    connect(lev,&ChooseLevelScene::selectmainback,[=](){
        lev->hide();
        this->show();
    });
    connect(btn,&QPushButton::clicked,[=](){
        btn->zoom1();
        btn->zoom2();
        QTimer::singleShot(500,this,[=](){
            this->hide();
            lev->show();
        });

    });

}
void MainScene::paintEvent(QPaintEvent *event){
    QPainter penter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    //penter.drawPixmap(0,0,pix);
    penter.drawPixmap(0,0,this->width(),this->height(),pix);
    pix.load(":/res/Title.png");
    pix.scaled(pix.width()*0.5,pix.height()*0.5);
    penter.drawPixmap(10,30,pix.width(),pix.height(),pix);



}
MainScene::~MainScene()
{
    delete ui;
}

