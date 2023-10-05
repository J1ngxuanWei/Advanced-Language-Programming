#include "pcscene.h"
#include<gamebutton.h>
#include<player.h>
#include<QPainter>
#include<QPaintEvent>
#include<QDebug>
#include<QVector>
#include<vector>
#include<time.h>
#include<QTime>
#include<ctime>
#include<QMessageBox>
#include<QFile>
#include<QSound>
#include<QDesktopServices>
#include<QTimer>


#define before ":/new/resources/start_ui.png"
#define back_game ":/new/resources/play_ground.jpg"
#define ground_pic ":/new/resources/ground.png"
#define hurtpic ":/new/resources/hurt.png"
#define gameover ":/new/resources/death.png"
#define pause ":/new/resources/pause.png"

//音效
#define jump ":/sou/sound/jump.wav"
#define coin_pic ":/sou/sound/coin.wav"
#define over ":/sou/sound/over.wav"
#define collision ":/sou/sound/collision.wav"



pcscene::pcscene(QWidget *parent,int wid,int hei) : QWidget(parent)
{
    this->resize(wid,hei);
    ground_Y=hei-70;

    //加载图片
    background.load(back_game);
    before_start.load(before);
    ground.load(ground_pic);
    hurtImg.load(hurtpic);
    pauseImg.load(pause);
    gameOverImg.load(gameover);


    //初始化人物按键操作
    up=0;
    down=0;
    left=0;
    right=0;
    difficult=0;

    isRuning=0;
    isPause=0;
    ground_speed=1;
    ground_X=0;
    Score=0;
    beforegame=1;
    Coinnum=0;

    remove.setInterval(17);

    this->grabKeyboard();

    //时间事件处理
/*
    connect(&r->zidan_Timer,&QTimer::timeout,[=]()
    {
        r->addzidan();
    });
*/

    connect(&remove,&QTimer::timeout,[=]()
    {
        //重新装弹
        connect(&r->zidan_Timer,&QTimer::timeout,[=]()
        {
            r->addzidan();
        });
        
        //boss行为判断改变
        connect(&rr->do_action,&QTimer::timeout,[=]()
        {
            int xxx=rand()%4;
            if(xxx==0)
            {
                rr->jingzhi_=1;
                rr->pugong_=0;
                rr->jineng1_=0;
                rr->jineng2_=0;
            }
            else if(xxx==1)
            {
                rr->jingzhi_=0;
                rr->pugong_=1;
                rr->jineng1_=0;
                rr->jineng2_=0;
            }
            else if(xxx==2)
            {
                rr->jingzhi_=0;
                rr->pugong_=0;
                rr->jineng1_=1;
                rr->jineng2_=0;
            }
            else if(xxx==3)
            {
                rr->jingzhi_=0;
                rr->pugong_=0;
                rr->jineng1_=0;
                rr->jineng2_=1;
            }
        });
        

        r->move(up,down,right,left);
        if(difficult<=80)
        {
            difficult+=0.001;
        }
        else
        {
            difficult=80;
        }

        //核心部分，障碍物生成
        //忍币

        for(auto i=obstacle1.begin();i!=obstacle1.end();i++)
        {
            if((*i)->done())
            {
                i=obstacle1.erase(i);
            }
            else
            {
                if((*i)->ispengzhuang(r->getx()-5,r->gety()-5,r->getwid()-5,r->getwid()-5))
                {
                    QSound::play(coin_pic);
                    r->setScore(2000);//吃币加分
                    obstacle1.erase(i);
                    Coinnum++;
                    break;
                }
                if(!obstacle1.empty())
                {
                    (*i)->move();
                }
            }
        }
        //飞箭
        for(auto i=obstacle2.begin();i!=obstacle2.end();i++)
        {
            if((*i)->done())
            {
                i=obstacle2.erase(i);
            }
            else
            {
                if((*i)->ispengzhuang(r->getx()-5,r->gety()-5,r->getwid()-5,r->getwid()-5))
                {
                    QSound::play(collision);
                    r->reducehp();
                    if(r->getScore()>2000)goto K;
                    if(r->getScore()>=100)
                    {
                        r->setScore(-100);
                    }
                    else
                    {
                        r->setScore(0);
                    }
                    K:;
                    hurtImgAlpha=255;
                    obstacle2.clear();

                    break;
                }
                if(!obstacle2.empty())
                {
                    (*i)->move();
                }
            }
        }
        //飞镖
        for(auto i=obstacle3.begin();i!=obstacle3.end();i++)
        {
            if((*i)->done())
            {
                i=obstacle3.erase(i);
            }
            else
            {
                if((*i)->ispengzhuang(r->getx()-5,r->gety()-5,r->getwid()-5,r->getwid()-5))
                {
                    QSound::play(collision);
                    r->reducehp();
                    if(r->getScore()>2000)goto Kk;
                    if(r->getScore()>=100)
                    {
                        r->setScore(-100);
                    }
                    else
                    {
                        r->setScore(0);
                    }
                    Kk:;
                    hurtImgAlpha=255;
                    obstacle3.clear();

                    break;
                }
                if(!obstacle3.empty())
                {
                    (*i)->move();
                }
            }
        }
        //子弹
        for(auto p=obstacle4.begin();p!=obstacle4.end();p++)
        {
            if((*p)->done())
            {
                p=obstacle4.erase(p);
            }
            else
            {
                for(auto i=obstacle2.begin();i!=obstacle2.end();i++)
                {
                    if((*p)->ispengzhuang((*i)->getx()-5,(*i)->gety()-5,(*i)->getwid()-5,(*i)->getwid()-5))
                    {
                        QSound::play(collision);
                        (*p)->sety(2000);
                        (*i)->sety(-50);
                        goto L;
                    }
                }
                for(auto i=obstacle3.begin();i!=obstacle3.end();i++)
                {
                    if((*p)->ispengzhuang((*i)->getx()-5,(*i)->gety()-5,(*i)->getwid()-5,(*i)->getwid()-5))
                    {
                        QSound::play(collision);
                        (*p)->sety(2000);
                        (*i)->sety(-50);
                        goto L;
                    }
                }

                if((*p)->ispengzhuang(rr->x-5,rr->y-5,rr->wid-5,rr->hei-5))
                {
                    QSound::play(collision);
                    (*p)->sety(2000);
                    rr->reducehp();
                    goto L;
                }

                if(!obstacle4.empty())
                {
                    (*p)->move();
                }
            }
            L:;
        }

        //普攻
        for(auto i=obstacle5.begin();i!=obstacle5.end();i++)
        {
            if((*i)->done())
            {
                i=obstacle5.erase(i);
            }
            else
            {
                if((*i)->ispengzhuang(r->getx()-5,r->gety()-5,r->getwid()-5,r->getwid()-5))
                {
                    QSound::play(collision);
                    r->reducehp();
                    if(r->getScore()>=100)
                    {
                        r->setScore(-100);
                    }
                    else
                    {
                        r->setScore(0);
                    }
                    hurtImgAlpha=255;
                    i=obstacle5.erase(i);
                    break;
                }
                if(!obstacle5.empty())
                {
                    (*i)->move();
                }
            }
        }

        //技能1
        for(auto i=obstacle6.begin();i!=obstacle6.end();i++)
        {
            if((*i)->done())
            {
                i=obstacle6.erase(i);
            }
            else
            {
                if((*i)->ispengzhuang(r->getx()-5,r->gety()-5,r->getwid()-5,r->getwid()-5))
                {
                    QSound::play(collision);
                    r->reducehp();
                    if(r->getScore()>=100)
                    {
                        r->setScore(-100);
                    }
                    else
                    {
                        r->setScore(0);
                    }
                    hurtImgAlpha=255;
                    i=obstacle6.erase(i);
                    break;
                }
                if(!obstacle6.empty())
                {
                    (*i)->move();
                }
            }
        }

        //技能2
        static int hurttime=30;
        for(auto i=obstacle7.begin();i!=obstacle7.end();i++)
        {
            if((*i)->done())
            {
                i=obstacle7.erase(i);
            }
            else
            {
                if(hurttime>1)goto LI;
                if((*i)->ispengzhuang(r->getx()-5,r->gety()-5,r->getwid()-5,r->getwid()-5))
                {
                    QSound::play(collision);
                    r->reducehp();
                    hurttime=30;
                    hurtImgAlpha=255;
                    break;
                }
                LI:
                if(!obstacle7.empty())
                {
                    hurttime--;
                    (*i)->move();
                }
            }
        }

        //红心
        for(auto i=obstacle8.begin();i!=obstacle8.end();i++)
        {
            if((*i)->done())
            {
                i=obstacle8.erase(i);
            }
            else
            {
                if((*i)->ispengzhuang(r->getx()-5,r->gety()-5,r->getwid()-5,r->getwid()-5))
                {
                    r->increasehp(300);
                    obstacle8.erase(i);
                    break;
                }
                if(!obstacle8.empty())
                {
                    (*i)->move();
                }
            }
        }







        if(isRuning)
        {
            if(r->gethp()<=0)
            {
                gameIsOver();//结束游戏
            }

            addobstacle();//增加障碍物函数
        }

        //音乐部分




    });
}



pcscene::~pcscene()
{
    delete r;
}




//绘制地图
void pcscene::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if(isRuning==0&&beforegame==1)//首页
    {
        painter.drawPixmap(0,0,this->width(),this->height(),QPixmap(before_start));
    }
    else if(GameOver==1)//结束
    {
        painter.drawPixmap(QRect(0,0,this->width(),this->height()),gameOverImg);
    }
    else//游戏中
    {
        //背景图片

/*      painter.drawPixmap(QRect(0,0,this->width(),this->height())
                     ,background
                     ,QRect(backImgX[0],0,this->width(),this->height()));  //在指定区域绘制指定尺寸的图片
        if(backImgX[0]>0)
        {
            painter.drawPixmap(QRect(background.width()-backImgX[0],0,this->width()-(background.width()-backImgX[0]),this->height())
                         ,background
                         ,QRect(0,0,this->width()-(background.width()-backImgX[0]),this->height()));   //补充右边的空白区域
        }
        if(backImgX[0]>=background.width())
        {
              backImgX[0]-=background.width();
        }
        if(isRuning&&isPause==false)
        {
            backImgX[0]+=imgSpeed[0]; //图片剪切区域x起点
        }
*/

        painter.drawPixmap(QRect(0,0,this->width(),this->height()),background);

        //地面
        painter.drawPixmap(QRect(0,ground_Y,this->width(),this->height()-ground_Y),ground,QRect(ground_X,0,this->width(),this->height()- ground_Y));
        if(ground_X>ground.width()-this->width())   //补充空白
        {
            painter.drawPixmap(QRect(ground.width()-ground_X,this->ground_Y,this->width()-(ground.width()-ground_X),this->height()-this->ground_Y)
                         ,ground
                         ,QRect(0,0,this->width()-(ground.width()-ground_X),this->height()-this->ground_Y));
        }
        if(ground_X>=ground.width())
        {
             ground_X-=ground.width();
        }
        if(isRuning&&isPause==false)
        {
            ground_X+=ground_speed;
        }


        //人物
        painter.drawPixmap(QRect(r->getx(),r->gety(),r->getwid(),r->gethei()),r->getpic());

        //受伤
        if(hurtImgAlpha!=0)
        {
            QPixmap temp(hurtImg.size());

            temp.fill(Qt::transparent);
            QPainter p2(&temp);
            p2.setCompositionMode(QPainter::CompositionMode_Source);
            p2.drawPixmap(0,0,hurtImg);
            p2.setCompositionMode(QPainter::CompositionMode_DestinationIn);
            p2.fillRect(temp.rect(),QColor(0,0,0,hurtImgAlpha));
            painter.drawPixmap(QRect(0,0,this->width(),this->height()),temp);
            hurtImgAlpha-=3;
        }

        //血量、金币、分数

        //血量
        painter.drawRect(QRect(1000,50,150,10));
        painter.drawLine(1050,50,1050,60);
        painter.drawLine(1100,50,1100,60);
        //QPen pen1(Qt::white);
        painter.setFont(QFont("黑体",20));
        //pen1.setColor(Qt::white);
        painter.setPen(Qt::white);
        painter.drawText(100,695,QString("HP:      %1%").arg(r->getbaifenzhihp()));



        //金币数量
        painter.drawText(100,50,QString("Coinnum:%1").arg(Coinnum)) ;

        //分数
        painter.drawText(100,150,QString("Score:%1").arg(r->getScore()));


        //子弹数显示
        painter.drawText(100,100,QString("Bullet:%1").arg(r->getzidan()));




        //障碍物
        for(auto i=obstacle1.begin();i!=obstacle1.end();i++)
        {
            painter.drawPixmap(QRect((*i)->getx(),(*i)->gety(),(*i)->getwid(),(*i)->gethei()),(*i)->getpic());
        }
        for(auto i=obstacle2.begin();i!=obstacle2.end();i++)
        {
            painter.drawPixmap(QRect((*i)->getx(),(*i)->gety(),(*i)->getwid(),(*i)->gethei()),(*i)->getpic());
        }
        for(auto i=obstacle3.begin();i!=obstacle3.end();i++)
        {
            painter.drawPixmap(QRect((*i)->getx(),(*i)->gety(),(*i)->getwid(),(*i)->gethei()),(*i)->getpic());
        }
        //子弹
        for(auto i=obstacle4.begin();i!=obstacle4.end();i++)
        {
            painter.drawPixmap(QRect((*i)->getx(),(*i)->gety(),(*i)->getwid(),(*i)->gethei()),(*i)->getpic());
        }

        //技能、普攻
        for(auto i=obstacle5.begin();i!=obstacle5.end();i++)
        {
            painter.drawPixmap(QRect((*i)->getx(),(*i)->gety(),(*i)->getwid(),(*i)->gethei()),(*i)->getpic());
            //qDebug()<<"pg";
        }
        for(auto i=obstacle6.begin();i!=obstacle6.end();i++)
        {
            if((*i)->getx()<=800)
            {
                (*i)->speed=200;
            }
            painter.drawPixmap(QRect((*i)->getx(),(*i)->gety(),(*i)->getwid(),(*i)->gethei()),(*i)->getpic());
        }
        for(auto i=obstacle7.begin();i!=obstacle7.end();i++)
        {
            painter.drawPixmap(QRect((*i)->getx(),(*i)->gety(),(*i)->getwid(),(*i)->gethei()),(*i)->getpic());
        }

        //红心
        for(auto i=obstacle8.begin();i!=obstacle8.end();i++)
        {
            painter.drawPixmap(QRect((*i)->getx(),(*i)->gety(),(*i)->getwid(),(*i)->gethei()),(*i)->getpic());
        }





        //暂停画面
        if(isPause&&!GameOver)
        {
            painter.drawPixmap(QRect(0,0,this->width(),this->height()),pauseImg);
        }





        QPainter hp_painter(this);
        QBrush red_brush( QColor("#F20900") );//把刷子设置为红色
        hp_painter.setBrush(red_brush);//应用刷子
        float rate = 1.0*r->gethp()/r->maxhp;//计算比例
        float bo_rate=1.0*rr->hp/rr->maxhp;
        hp_painter.drawRect(150,669,rate*100,30);//绘制人物血量



        //BOSS出场
        if(Coinnum>100&&rr->hp>0)
        {
            rr->live=1;
            painter.drawPixmap(QRect(rr->x,rr->y,rr->wid,rr->hei),rr->getpic());
            hp_painter.drawRect(510,50,bo_rate*700,30);//绘制Boss血量

            QPainter bo_painter(this);
            bo_painter.setFont(QFont("黑体",20));
            bo_painter.setPen(Qt::white);
            bo_painter.drawText(430,75,QString("Boss:                                     %1%").arg(rr->getbaifenzhihp()));

        }
        rr->die();




        update();
    }
}

//添加障碍物
void pcscene::addobstacle()
{
    static int Lastcoin_time;
    if(Lastcoin_time>=30-difficult)
    {
        int x=this->width()+5;
        int y=ground_Y-18-rand()%300;
        obstacle1.push_back(new coin(x,y,20,20));
        Lastcoin_time=0;
    }
    Lastcoin_time++;

    static int Lastheart_time;
    if(Lastheart_time>=120-difficult)
    {
        int x=this->width()+5;
        int y=ground_Y-18-rand()%300;
        obstacle8.push_back(new redheart(x,y,40,40));
        Lastheart_time=0;
    }
    Lastheart_time++;


    static int Lastfarrow_time;
    if(Lastfarrow_time>=100-difficult)
    {
        int x=this->width()+100;
        int y=ground_Y-90-rand()%400;
        obstacle2.push_back(new farrow(x,y,200,50));
        Lastfarrow_time=0;
    }
    Lastfarrow_time++;

    static int Lastfbbb_time;
    if(Lastfbbb_time>=220-difficult)
    {
        int x=this->width()+100;
        int y=ground_Y-90-rand()%400;
        obstacle3.push_back(new fbbb(x,y,70,70));
        Lastfbbb_time=0;
    }
    Lastfbbb_time+=2;

    static int pugong_time;
    if(rr->live&&rr->pugong_&&pugong_time>60)
    {
        int x=rr->x;
        int y=560;
        obstacle5.push_back(new pug(x,y,200,80));
        pugong_time=0;
    }
    pugong_time++;
    if(!rr->pugong_)
    {
        obstacle5.clear();
    }

    static int jineng1_time;
    if(rr->live&&rr->jineng1_&&jineng1_time>80)
    {
        int x=rr->x;
        int y=500-rand()%400;
        jin1 *ppp=new jin1(x,y,600,200);
        ppp->jineng_Timer.start();
        obstacle6.push_back(ppp);
        jineng1_time=0;
    }
    jineng1_time++;
    if(!rr->jineng1_)
    {
        obstacle6.clear();
    }


    static int jineng2_time;
    static int jineng2_num=0;
    if(rr->live&&rr->jineng2_&&jineng2_time>80)
    {
        if(jineng2_num==1)goto LO;
        int x=rr->x;
        int y=500;
        jin2 *ppp=new jin2(x,y,600,200);
        ppp->jineng_Timer.start();
        obstacle7.push_back(ppp);
        jineng2_time=0;
        jineng2_num=1;
    }
    LO:
    jineng2_time++;
    if(!rr->jineng2_)
    {
        jineng2_num=0;
        obstacle7.clear();
    }





}

void pcscene::start_game()
{
    r=new player(this);
    r->run_Timer.start();
    remove.start();
    r->hp_Timer.start();
    r->zidan_Timer.start();

    rr=new Boss();
    rr->action.start();
    rr->do_action.start();\



    GameOver=0;
    beforegame=0;
    isRuning=1;
    Coinnum=0;
    isPause=0;
    update();
}

//键盘响应
void pcscene::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_W)
    {
        up=true;
        QSound::play(jump);
    }
    else if(event->key()==Qt::Key_S)
    {
        down=true;
    }
    else if(event->key()==Qt::Key_D)
    {
        right=true;
    }
    else if(event->key()==Qt::Key_A)
    {
        left=true;
    }
    else if(event->key()==Qt::Key_J)
    {
        shott();
    }
    else if(!GameOver&&event->key()==Qt::Key_Escape)
    {
        if(isPause==false)
        {
            r->hp_Timer.stop();
            gamepause();

        }
        else
        {
            r->hp_Timer.start();
            gamecontinue()  ;
        }
    }
    else if(!GameOver && isRuning&&!isPause&&event->key()==Qt::Key_Q)
    {
         r->dashmove_() ;
    }
    else if(GameOver && event->key()==Qt::Key_R)
    {
        start_game();
    }
    else if(GameOver&&event->key()==Qt::Key_B)
    {
        back();
    }
    else
    {
        return QWidget::keyPressEvent(event);
    }

}

void pcscene::back()
{
    beforegame=1;
    button->move(900,400);
    button_2->show();
    update();
}

void pcscene::gamepause()
{
    isPause = true;
    remove.stop() ;
    r->pauseplayer();
    rr->action.stop();
    rr->do_action.stop();

}

void pcscene::gamecontinue()
{
    isPause = false;
    remove.start() ;
    r->continueplayer();
    rr->action.stop();
    rr->do_action.stop();

}

//键盘松开的时候进行的复位操作
void pcscene::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_W)
    {
        up=false;
        //qDebug()<<up;
    }
    else if(event->key()==Qt::Key_S)
    {
        down=false;
    }
    else if(event->key()==Qt::Key_D)
    {
        right=false;
    }
    else if(event->key()==Qt::Key_A)
    {
        left=false;
    }
    else
    {
        return QWidget::keyPressEvent(event);
    }

}

void pcscene::gameIsOver()
{
    QSound::play(over);
    Score=r->getScore();



    isRuning=0;
    GameOver=1;


    remove.stop();
    obstacle1.clear();
    obstacle2.clear();
    obstacle3.clear();


    r->run_Timer.stop();
    r->zidan_Timer.stop();
    rr->action.stop();
    rr->do_action.stop();


    delete r;
    delete rr;
    update();
}

void pcscene::shott()
{
    if(!r->shot())return;
    r->zidanshu--;
    bullet *p=new bullet(r->getx()+20,r->gety(),20,20);
    obstacle4.push_back(p);

}

