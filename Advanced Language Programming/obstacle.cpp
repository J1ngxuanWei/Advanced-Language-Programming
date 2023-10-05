#include "obstacle.h"

#include<QTimer>
#include<QDebug>


#define coin_1 ":/new/resources/coin.png"
#define fj ":/new/resources/feijian.png"
#define fb ":/new/resources/feibiao.png"
#define bullet_pic ":/new/resources/bullet.png"
#define pug_ ":/new/resources/pugong.png"
#define redhea ":/new/resources/blood.png"

//基类
obstacle::obstacle(int x,int y,int width,int height)
{
    this->x=x;
    this->y=y;
    this->width=width;
    this->height=height;
    curji=0;
    jineng_Timer.setInterval(100);
    connect(&jineng_Timer,&QTimer::timeout,
            [=]()
            {
               curji=(curji+1)%4;
            }
      );//技能图片的切换

}
int obstacle::getx()
{
    return this->x;
}
int obstacle::gety()
{
    return this->y;
}
void obstacle::setx(int x)
{
    this->x=x;
}
void obstacle::sety(int y)
{
    this->y=y;
}
int obstacle::getwid()
{
    return this->width;
}
int obstacle::gethei()
{
    return this->height;
}


//忍币
coin::coin(int x, int y, int wid, int hei):obstacle(x,y,wid,hei)
{
    this->pic.load(coin_1);
}

QPixmap coin::getpic()
{
    return this->pic;
}

bool coin::ispengzhuang(int lx, int ly, int wid, int hei)
{
    QRect rect_1(this->getx(),this->gety(),this->getwid()-20,this->gethei()+20);
    QRect rect_2(lx,ly,wid,hei);
    return rect_1.intersects(rect_2);    //返回两个矩形是否发生碰撞的结果
}


void coin::move()
{
    this->setx(this->getx()-5);
}

bool coin::done()
{
    if(this->getx()<-10)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


//红心
redheart::redheart(int x, int y, int wid, int hei):obstacle(x,y,wid,hei)
{
    this->pic.load(redhea);
}

QPixmap redheart::getpic()
{
    return this->pic;
}

bool redheart::ispengzhuang(int lx, int ly, int wid, int hei)
{
    QRect rect_1(this->getx(),this->gety(),this->getwid()-20,this->gethei()+20);
    QRect rect_2(lx,ly,wid,hei);
    return rect_1.intersects(rect_2);    //返回两个矩形是否发生碰撞的结果
}


void redheart::move()
{
    this->setx(this->getx()-5);
}

bool redheart::done()
{
    if(this->getx()<-10)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


//飞箭
farrow::farrow(int x, int y, int wid, int hei):obstacle(x,y,wid,hei)
{
    this->pic.load(fj);

}

QPixmap farrow::getpic()
{
    return this->pic;
}


bool farrow::ispengzhuang(int lx, int ly, int wid, int hei)
{
    QRect rect_1(this->getx(),this->gety(),this->getwid(),this->gethei());
    QRect rect_2(lx,ly,wid,hei);
    return rect_1.intersects(rect_2);    //返回两个矩形是否发生碰撞的结果

}

void farrow::move()
{
    this->setx(this->getx()-10);
}
bool farrow::done()
{
    if(this->getx()<-10)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
//飞镖

fbbb::fbbb(int x, int y, int wid, int hei):obstacle(x,y,wid,hei)
{
    this->pic.load(fb);

}

QPixmap fbbb::getpic()
{
    return this->pic;
}

bool fbbb::ispengzhuang(int lx, int ly, int wid, int hei)
{
    QRect rect_1(this->getx(),this->gety(),this->getwid()-100,this->gethei()-20);
    QRect rect_2(lx,ly,wid,hei);
    return rect_1.intersects(rect_2);    //返回两个矩形是否发生碰撞的结果

}

void fbbb::move()
{
    this->setx(this->getx()-10);
}
bool fbbb::done()
{
    if(this->getx()<-10)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//子弹
bullet::bullet(int x, int y, int wid, int hei):obstacle(x,y,wid,hei)
{
    this->pic.load(bullet_pic);

}

QPixmap bullet::getpic()
{
    return this->pic;
}

bool bullet::ispengzhuang(int lx, int ly, int wid, int hei)
{
    QRect rect_1(this->getx(),this->gety(),this->getwid()-100,this->gethei()-20);
    QRect rect_2(lx,ly,wid,hei);
    return rect_1.intersects(rect_2);    //返回两个矩形是否发生碰撞的结果

}

void bullet::move()
{
    this->setx(this->getx()+10);
}
bool bullet::done()
{
    if(this->getx()<+10)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


//普攻
pug::pug(int x, int y, int wid, int hei):obstacle(x,y,wid,hei)
{
    this->pic.load(pug_);
}

QPixmap pug::getpic()
{
    return this->pic;
}

bool pug::ispengzhuang(int lx, int ly, int wid, int hei)
{
    QRect rect_1(this->getx(),this->gety(),this->getwid(),this->gethei());
    QRect rect_2(lx,ly,wid,hei);
    return rect_1.intersects(rect_2);    //返回两个矩形是否发生碰撞的结果

}

void pug::move()
{
    this->setx(this->getx()-10);
}
bool pug::done()
{
    if(this->getx()<-210)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


//技能1
jin1::jin1(int x, int y, int wid, int hei):obstacle(x,y,wid,hei)
{
    for(int i=0;i<4;i++)
    {
        pic[i].load(QString(":/new/resources/1%1.png").arg(i+1));
    }
    this->speed=0;
}

QPixmap jin1::getpic()
{
    return this->pic[curji];
}

bool jin1::ispengzhuang(int lx, int ly, int wid, int hei)
{
    QRect rect_1(this->getx(),this->gety(),this->getwid(),this->gethei());
    QRect rect_2(lx,ly,wid,hei);
    return rect_1.intersects(rect_2);    //返回两个矩形是否发生碰撞的结果

}

void jin1::move()
{
    this->setx(this->getx()-3-speed);
}
bool jin1::done()
{
    if(this->getx()<-10)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//技能2
jin2::jin2(int x, int y, int wid, int hei):obstacle(x,y,wid,hei)
{
    for(int i=0;i<4;i++)
    {
        pic[i].load(QString(":/new/resources/2%1.png").arg(i+1));
    }
    zuo=1;
    shang=0;
    you=0;
    xia=0;
}

QPixmap jin2::getpic()
{
    return this->pic[curji];
}

bool jin2::ispengzhuang(int lx, int ly, int wid, int hei)
{
    QRect rect_1(this->getx(),this->gety(),this->getwid(),this->gethei());
    QRect rect_2(lx,ly,wid,hei);
    return rect_1.intersects(rect_2);    //返回两个矩形是否发生碰撞的结果

}

void jin2::move()
{

    if(zuo)
    {
        this->setx(this->getx()-20);
    }
    else if(shang)
    {
        this->sety(this->gety()-20);
    }
    else if(you)
    {
        this->setx(this->getx()+20);
    }
    else if(xia)
    {
        this->sety(this->gety()+20);
    }

    if(zuo&&this->getx()<-10)
    {
        zuo=0;
        shang=1;

    }
    else if(shang&&this->gety()<-10)
    {
        shang=0;
        you=1;

    }
    else if(you&&this->getx()>800)
    {
        you=0;
        xia=1;
    }
    else if(xia&&this->gety()>500)
    {
        xia=0;
        zuo=1;
    }

}
bool jin2::done()
{
    if(this->getx()<-100)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
