#include "chooselevelscene.h"

ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(320,588);

    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));

    this->setWindowTitle("选择关卡场景");

    QMenuBar *bar =menuBar();
    setMenuBar(bar);

    QMenu * startmenu=bar->addMenu("开始");

    QAction * quitAction=startmenu->addAction("退出");

    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    QSound * chooseSound=new QSound(":/res/TapButtonSound.wav",this);
    QSound * backSound=new QSound(":/res/BackButtonSound.wav",this);

    MyPushButton *backBtn=new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width(),this->height()-backBtn->height());


    connect(backBtn,&MyPushButton::clicked,[=]()
    {
       //qDebug()<<"点击了返回按钮";
        backSound->play();


        QTimer::singleShot(500,this,[=](){
            emit this->chooseSceneBack();
        });
    });

    for(int i=0;i<20;i++)
    {
        MyPushButton * menuBtn=new MyPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(25+(i%4)*70,130+(i/4)*70);

        connect(menuBtn,&MyPushButton::clicked,[=]()
        {

            chooseSound->play();

            QString str=QString("您选择的是第%1关").arg(i+1);
            qDebug()<<str;

            this->hide();
            play=new playScene(i+1);
            play->setGeometry(this->geometry());
            play->show();



            connect(play,&playScene::chooseSceneBack,[=]()
            {
                this->setGeometry(play->geometry());
                this->show();
                delete play;
                play=NULL;
            });
        });


        QLabel * label=new QLabel;
        label->setParent(this);
        label->setFixedSize(menuBtn->width(),menuBtn->height());
        label->setText(QString::number(i+1));
        label->move(25+(i%4)*70,130+(i/4)*70);

        label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }
}

void ChooseLevelScene::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);

}
