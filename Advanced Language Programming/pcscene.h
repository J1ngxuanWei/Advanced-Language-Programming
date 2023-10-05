#ifndef PCSCENE_H
#define PCSCENE_H

#include <QWidget>
#include<QTimer>
#include<vector>

#include<obstacle.h>
#include<gamebutton.h>
#include<boss.h>

using namespace std;


class player;
class GameButton;
class pcscene : public QWidget
{
    Q_OBJECT
private:
    QPixmap background;  //游戏地图
    QPixmap before_start;   //开始前页面
    QPixmap ground;       //地面
    QPixmap pauseImg;
    player *r=0;
    Boss *rr=0;

    int hurtImgAlpha=0;
    QPixmap hurtImg;
    QPixmap gameOverImg;
public:
    ~pcscene();
    explicit pcscene(QWidget *parent = nullptr,int wid=1280,int hei=720);
    vector<coin *> obstacle1;//放忍币的容器
    vector<farrow *> obstacle2;//放飞箭的容器
    vector<fbbb *> obstacle3;//放飞镖的容器
    vector<bullet *> obstacle4;//放子弹的容器
    vector<redheart *>obstacle8;//放红心的容器

    vector<pug *> obstacle5;//放普攻的容器
    vector<jin1 *>obstacle6;//放技能1的容器
    vector<jin2 *>obstacle7;//放技能2的容器

    GameButton *button=0;
    GameButton *button_2=0;
    GameButton *button_3=0;
    GameButton *button_4=0;

    double backImgX[3]={0,200,0}; //图片水平移动参数
    double imgSpeed[3]={0.15,1,0.5};  //移动速度参数
    double ground_X;  //X点
    double ground_speed;   //地面移动参数
    int ground_Y;  //地面起点y值
    bool isRuning;  //是否游戏中
    bool isPause;  //是否暂停
    bool GameOver=false;
    bool beforegame;  //处于游戏开始前界面
    bool up;  //向上
    bool down;   //向下
    bool right;   //向右
    bool left ;
    int Coinnum ;  //金币数量
    int Score;
    double difficult;
    //bool esc;    //暂停
    //double difficult;  //控制游戏难度
    QTimer remove;
    void paintEvent(QPaintEvent *event);  //绘图
    void start_game(); //开始游戏
    void keyPressEvent(QKeyEvent *event);  //键盘按下事件
    void keyReleaseEvent(QKeyEvent *event);  //键盘释放事件
    void addobstacle();   //增加障碍物
    void gamepause();
    void gamecontinue();
    void dashmove();
    void gameIsOver();
    void restart();
    void back();  //返回首页
    void shott();
    int maxscore ;

signals:

public slots:
};

#endif // PCSCENE_H
