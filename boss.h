#ifndef BOSS_H
#define BOSS_H

#include <QObject>
#include <QWidget>
#include<QTimer>

class Boss: public QWidget
{
    Q_OBJECT
public:

    int hp;
    int maxhp;
    bool live;
    bool ceshi;
    QPixmap jingzhi[4];
    QPixmap pugong[2];
    QPixmap jineng1[2];
    QPixmap jineng2[2];


    Boss();
    QTimer action;
    QTimer do_action;
    QTimer ji_action;
    QTimer hpp_Timer;

    int x;
    int y;
    int wid;
    int hei;
    bool jingzhi_;
    bool pugong_;
    bool jineng1_;
    bool jineng2_;
    void reducehp();
    int getbaifenzhihp();
    QPixmap getpic();
    int curjing;
    int curpu;
    int curji1;
    int curji2;

    //技能部分
    void do_pugong();
    void do_jingzhi();
    void do_jineng1();
    void do_jineng2();


    void die();








signals:

public slots:
};

#endif // BOSS_H
