#include "playscene.h"
#include "mycoin.h"
//playScene::playScene(QWidget *parent) : QMainWindow(parent)
//{

//}
playScene::playScene(int levelNum)
{
    QString str=QString("进入了第%%1关").arg(levelNum);
    qDebug()<<str;
    this->levelIndex=levelNum;

    this->setFixedSize(320,558);

    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));

    this->setWindowTitle("翻金币场景");

    QMenuBar *bar =menuBar();
    setMenuBar(bar);

    QMenu * startmenu=bar->addMenu("开始");

    QAction * quitAction=startmenu->addAction("退出");

    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    QSound *backSound=new QSound(":/res/BackButtonSound.wav",this);

    QSound *flipSound=new QSound(":/res/ConFlipSound.wav",this);

    QSound *winSound=new QSound(":/res/LevelWinSound.wav",this);






    MyPushButton *backBtn=new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width(),this->height()-backBtn->height());


        connect(backBtn,&MyPushButton::clicked,[=]()
        {

           qDebug()<<"翻金币场景中，点击了返回按钮";
           backSound->play();
            QTimer::singleShot(500,this,[=](){
                this->hide();
                emit this->chooseSceneBack();
            });
        });
        //显示当前关卡数
        QLabel * label=new QLabel;
        label->setParent(this);
        QFont font;
        font.setFamily("华文新魏");
        font.setPointSize(20);
        QString str2=QString("Level:%1").arg(this->levelIndex);
        label->setFont(font);
        label->setText(str2);
        label->setGeometry(30,this->height()-50,120,50);

        dataConfig config;
        for(int i=0;i<4;i++)
        {
            for(int j=0;j<4;j++)
            {
                this->gameArray[i][j]=config.mData[this->levelIndex][i][j];
            }
        }

        QLabel * winLabel =new QLabel;
        QPixmap tmpPix;
        tmpPix.load(":/res/LevelCompletedDialogBg.png");
        winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
        winLabel->setPixmap(tmpPix);
        winLabel->setParent(this);
        winLabel->move((this->width()-tmpPix.width())*0.5,-tmpPix.height());


        for(int i=0;i<4;i++)
        {
            for(int j=0;j<4;j++)
            {
                //绘制背景图片
                QPixmap pix=QPixmap(":/res/BoardNode.png");
                QLabel * label=new QLabel;
                label->setGeometry(0,0,pix.width(),pix.height());
                label->setPixmap(pix);
                label->setParent(this);
                label->move(57+i*50,200+j*50);

                //创建金币
                QString str;
                if(this->gameArray[i][j]==1)
                {
                    str=":/res/Coin0001.png";
                }
                else
                {
                    str=":/res/Coin0008.png";
                }
                MyCoin * coin=new MyCoin(str);
                coin->setParent(this);
                coin->move(59+i*50,204+j*50);

                //给金币属性赋值
                coin->posX=i;
                coin->posY=j;
                coin->flag=this->gameArray[i][j];

                coinBtn[i][j]=coin;

                //点击金币 进行翻转
                connect(coin,&MyCoin::clicked,[=]()
                {
                    flipSound->play();
                    for(int i=0;i<4;i++)
                    {
                        for(int j=0;j<4;j++)
                        {
                            this->coinBtn[i][j]->isWin=true;
                        }
                    }
                    coin->changeFlag();
                    this->gameArray[i][j]=this->gameArray[i][j]==0 ? 1: 0;


                    QTimer::singleShot(300,this,[=](){
                        //翻转周围的硬币
                        //周围的右金币翻转条件
                        if(coin->posX+1<=3)
                        {
                            coinBtn[coin->posX+1][coin->posY]->changeFlag();
                            this->gameArray[coin->posX+1][coin->posY]=this->gameArray[coin->posX+1][coin->posY]==0 ? 1 : 0;
                        }
                        //周围的左金币翻转条件
                        if(coin->posX-1>=0)
                        {
                            coinBtn[coin->posX-1][coin->posY]->changeFlag();
                            this->gameArray[coin->posX-1][coin->posY]=this->gameArray[coin->posX-1][coin->posY]==0 ? 1 : 0;
                        }
                        //周围上侧的硬币翻转条件
                        if(coin->posY+1<=3)
                        {
                            coinBtn[coin->posX][coin->posY+1]->changeFlag();
                            this->gameArray[coin->posX][coin->posY+1]=this->gameArray[coin->posX][coin->posY+1]==0 ? 1 : 0;
                        }
                        //周围下侧硬币翻转条件
                        if(coin->posY-1>=0)
                        {
                            coinBtn[coin->posX][coin->posY-1]->changeFlag();
                            this->gameArray[coin->posX][coin->posY-1]=this->gameArray[coin->posX][coin->posY-1]==0 ? 1 : 0;
                        }


                        for(int i=0;i<4;i++)
                        {
                            for(int j=0;j<4;j++)
                            {
                                this->coinBtn[i][j]->isWin=false;
                            }
                        }

                        //判断是否胜利
                        this->isWin=true;
                        for(int i=0;i<4;i++)
                        {
                            for(int j=0;j<4;j++)
                            {
                                if(coinBtn[i][j]->flag==false)
                                {
                                    this->isWin=false;
                                    break;
                                }
                            }
                        }
                        if(this->isWin==true)
                        {
                            winSound->play();
                            qDebug()<<"游戏胜利";
                            for(int i=0;i<4;i++)
                            {
                                for(int j=0;j<4;j++)
                                {


                                   coinBtn[i][j]->isWin=true;

                                }
                            }

                            //将胜利的图片移动下来
                            QPropertyAnimation * animation=new QPropertyAnimation(winLabel,"geometry");
                            //设置时间间隔
                            animation->setDuration(1000);
                            //设置开始位置
                            animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                            //设置结束位置
                            animation->setEndValue(QRect(winLabel->x(),winLabel->y()+114,winLabel->width(),winLabel->height()));
                            animation->setEasingCurve(QEasingCurve::OutBounce);

                            animation->start();

                        }
                    });


                });
            }
        }
}

void playScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    pix.load(":/res/Title.png");

    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);

    painter.drawPixmap(10,30,pix);

}
