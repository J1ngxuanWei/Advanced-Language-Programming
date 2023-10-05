#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<gamebutton.h>
#include<pcscene.h>
#include<QPaintEvent>
#include<QPainter>
#include<QPushButton>
#include<QMessageBox>
#include<QMenu>
#include<QMenuBar>
#include<QSound>

#define button1 ":/new/resources/startbut_1.png"
#define button2 ":/new/resources/startbut_2.png"
#define button3 ":/new/resources/butt_1.png"
#define button4 ":/new/resources/butt_2.png"
#define starttitle ":/new/resources/title.png"
#define back_0  ":/new/resources/background.png"
#define title ":/new/resources/titl.png"

#define back_sound ":/sou/sound/start.wav"





MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSound *startsound=new QSound(back_sound,this);
    startsound->play();//播放背景音乐
    startsound->setLoops(-1); //设置单曲循环
    this->setFixedSize(1280,720);
    this->setWindowIcon(QPixmap(title)); //设置应用图标
    this->setWindowTitle("Darkest Dungeon");
    pc_widgt=new pcscene(this,this->width(),this->height());  //建立游戏类
    gamebutton1=new GameButton(button1,button2);  //建立按钮类
    gamebutton1->setParent(this);
    gamebutton1->move(500,500);
    gamebutton2=new GameButton(button3,button4);  //建立按钮类
    gamebutton2->setParent(this);
    gamebutton2->move(650,500);
    QString str_0=  "游 戏 玩 法 :\n"
                    "1.点击开始以进入游戏。\n"
                    "2.死亡后按R键重生再次开始游戏。\n"
                    "3.按Esc键暂停游戏。\n"
                    "4.按WSAD键进行移动，躲避障碍物。\n"
                    "5.按J键射击，每次射击消耗一发子弹。\n"
                    "   子弹最多有4个，每隔一段时间会重新装弹。\n"
                    "6.碰到障碍物会扣血，血量为0游戏结束。\n"
                    "7.吃金币可以增加得分，碰到障碍物会减分。\n"
                    "8.金币达到100个时将会召唤Boss。\n"
                    "   射击可对Boss造成伤害。\n"
                    "                         Good luck!!\n"
                    "  The Darkest Dungeon is waiting for you!!"
                    ;


    connect(gamebutton2,&QPushButton::clicked,this,
            [=]()
            {
                 QMessageBox::about(this,"游 戏 玩 法",str_0);

            }
               );
    connect(gamebutton1,&QPushButton::clicked,this,
            [=]()
            {
                //qDebug()<<"开始";

                start=new QPropertyAnimation(gamebutton1,"geometry");
                start->setDuration(300);
                start->setEasingCurve(QEasingCurve::OutQuad);
                start->setStartValue(QRect(gamebutton1->x(),gamebutton1->y(),gamebutton1->width(),gamebutton1->height()));
                start->setEndValue(QRect(gamebutton1->x(),750,gamebutton1->width(),gamebutton1->height()));
                start->start();
                pc_widgt->isRuning=true;
                pc_widgt->button=gamebutton1;
                pc_widgt->button_2=gamebutton2;
                pc_widgt->start_game();
                gamebutton2->hide();
            }
               );

}

MainWindow::~MainWindow()
{
    delete ui;
    delete start;
    delete gamebutton1;
    delete pc_widgt;

}
