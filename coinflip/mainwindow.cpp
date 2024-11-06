#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mypushbutton.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFixedSize(320,588);

    setWindowIcon(QIcon(":/res/Coin0001.png"));

    setWindowTitle("翻金币主场景");

    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });

    QSound * startSound=new QSound(":/res/TapButtonSound.wav");

    MyPushButton * startBtn=new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.7);

    ChooseLevelScene * chooseScene = new ChooseLevelScene();

    connect(chooseScene,&ChooseLevelScene::chooseSceneBack,this,[=]()
    {
            this->setGeometry(chooseScene->geometry());
            chooseScene->hide();
            this->show();
});

    connect(startBtn,&MyPushButton::clicked,[=]()
    {
        qDebug()<<"点击开始了";

        startSound->play();


        startBtn->zoom1();
        startBtn->zoom2();


        QTimer::singleShot(500,this,[=](){

            chooseScene->setGeometry(this->geometry());

            this->hide();

            chooseScene->show();


        });



            });


}


void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    pix.load(":/res/Title.png");

    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);

    painter.drawPixmap(10,30,pix);


}


MainWindow::~MainWindow()
{
    delete ui;
}


