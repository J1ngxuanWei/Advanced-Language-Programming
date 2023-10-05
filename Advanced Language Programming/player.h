#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include<pcscene.h>
#include<QTimer>
#include<boss.h>


class player : public QWidget
{
    Q_OBJECT
private:
    QPixmap run_pic[5];  //奔跑图片
    QPixmap jump_pic;  //跳跃图片
    //设置计时器，作为奔跑的下标
    int currunpic;
    //设置人物的长和宽，实质为矩形
    int wid;
    int hei;
    //人物的位置坐标
    int x;
    int y;
    //人物的血量

    int curRunpic=0;
    int score=0;//分数

    //射击


public:
    //explicit player(QWidget *parent = nullptr);
    pcscene *game;
    player(pcscene *game);
    QTimer run_Timer;  //定时器
    QTimer jump_Timer;//防止跳起来掉不下来（bushi）
    QTimer hp_Timer ;
    QTimer zidan_Timer;

    //
    int zidanshu;
    int hp;
    int maxhp;



    bool jump_once;  //已经跳了一次，判断能不能二段跳的
    bool jump_twice;  //已经跳了两次
    bool in_fall;  //正在下落
    bool twice_jumpready;  //可以二次跳
    double fall_speed;  //下落速度
    double fallspeed_a;  //下落加速度，不然感觉不太科学，后期要优化手感
    double jump_speed;  //上升速度
    int jump_h;  //一次跳跃高度
    int getx();
    int gety();
    int getwid();
    int gethei();
    void setScore(int n);
    int getScore();
    void move(bool up,bool down,bool right,bool left);  //人物坐标移动
    QPixmap getpic();
    void pauseplayer();
    void continueplayer();

    //射击设置
    bool shot();
    void addzidan();
    int getzidan();



    //血量设置
    void reducehp();
    void increasehp(int n);
    int gethp();
    int getbaifenzhihp();//获得处理后的血量的

    void dashmove_();

    void addscore(int s);//加分的

signals:

public slots:
};

#endif // PLAYER_H
