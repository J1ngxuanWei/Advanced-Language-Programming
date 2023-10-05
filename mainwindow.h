#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<gamebutton.h>
#include<QPropertyAnimation>
#include<pcscene.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    GameButton *gamebutton1=0;
    GameButton *gamebutton2=0;
    GameButton *gamebutton3=0;
    GameButton *gamebutton4=0;
    pcscene *pc_widgt=0;


    QPropertyAnimation *start=0;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
