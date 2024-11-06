#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include <QDebug>
#include <QPainter>
#include <QMenuBar>
#include <QTimer>
#include <QLabel>
#include <QDebug>
#include <QPropertyAnimation>
#include"dataconfig.h"
#include"mypushbutton.h"
#include"mycoin.h"
#include<QSound>
class playScene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit playScene(QWidget *parent = nullptr);


    playScene(int levelNum);

    int levelIndex;

    void paintEvent(QPaintEvent *);


    int gameArray[4][4];

    MyCoin * coinBtn[4][4];

    bool isWin=false;
signals:
    void chooseSceneBack();
};

#endif // PLAYSCENE_H
