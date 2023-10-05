#include "boss.h"
#include<QTimer>
#include<pcscene.h>
#include<QDebug>

#define jingzhi_1 ":/new/resources/jingzhi1.png"
#define jingzhi_2 ":/new/resources/jingzhi2.png"
#define jingzhi_3 ":/new/resources/jingzhi3.png"
#define jingzhi_4 ":/new/resources/jingzhi4.png"

#define pugong_1 ":/new/resources/pugong1.png"
#define pugong_2 ":/new/resources/pugong2.png"

#define jineng_11 ":/new/resources/qishoushi.png"
#define jineng_12 ":/new/resources/jineng1.png"

#define jineng_21 ":/new/resources/qishoushi.png"
#define jineng_22 ":/new/resources/jineng2.png"

static int boss_ac=0;

Boss::Boss()
{
    action.setInterval(300);
    do_action.setInterval(5000);
    ji_action.setInterval(100);
    x=1030;
    y=160;
    wid=340;
    hei=500;
    hp=10000;
    maxhp=10000;
    jingzhi_=1;
    pugong_=0;
    jineng1_=0;
    jineng2_=0;

    live=0;

    //加载图片
    for(int i=0;i<4;i++)
    {
        jingzhi[i].load(QString(":/new/resources/jingzhi%1.png").arg(i+1));
    }
    for(int i=0;i<2;i++)
    {
        pugong[i].load(QString(":/new/resources/pugong%1.png").arg(i+1));
    }
    for(int i=0;i<2;i++)
    {
        jineng1[i].load(QString(":/new/resources/jineng1%1.png").arg(i+1));
    }
    for(int i=0;i<2;i++)
    {
        jineng2[i].load(QString(":/new/resources/jineng2%1.png").arg(i+1));
    }

    curjing=0;
    curpu=0;
    curji1=0;
    curji2=0;


    connect(&action,&QTimer::timeout,
            [=]()
            {
        if(jingzhi_)
        {
                       curjing=(curjing+1)%4;
        }
        else if(pugong_)
        {
                       curpu++;
                       curpu=curpu%2;
        }
        else if(jineng1_)
        {
                       curji1=(curji1+1)%2;
        }
        else if(jineng2_)
        {
                       curji2=(curji2+1)%2;
        }




            }
      );

    hpp_Timer.setInterval(20);  //设定每帧时长
    connect(&hpp_Timer,&QTimer::timeout,
            [=]()
            {
                    if(hp<maxhp)
                    {
                        hp+=10 ;
                    }

            }
      );





}

void Boss::reducehp()
{
    hp-=200;
}

int Boss::getbaifenzhihp()
{
    return this->hp*100/this->maxhp;
}

QPixmap Boss::getpic()
{
    QPixmap pic;
/*    if(boss_ac==30)
    {
        boss_ac=0;
        jingzhi_=1;
        pugong_=0;
        jineng1_=0;
        jineng2_=0;
    }
*/
    if(jingzhi_)
    {
        //qDebug()<<"w";
        pic=jingzhi[curjing];
    }
    else if(pugong_)
    {
        //qDebug()<<"ww";
        boss_ac++;
        pic=pugong[curpu];
    }
    else if(jineng1_)
    {
        //qDebug()<<"www";
        boss_ac++;
        pic=jineng1[curji1];
    }
    else if(jineng2_)
    {
        //qDebug()<<"wwww";
        boss_ac++;
        pic=jineng2[curji2];
    }

    return pic;
}

void Boss::die()
{
    if(this->hp<=0)live=0;
}
