#include "chooselevelscene.h"
#include<QPainter>
#include<QMenu>
#include<QMenuBar>
#include<QPixmap>
#include "mypushbutton.h"
#include<QTimer>
#include<QLabel>
#include<QDebug>
#include "playsence.h"
#include<QSound>
ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{ //配置选择关卡场景
this->setFixedSize(520,888);
    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置标题
    this->setWindowTitle("选择关卡场景");
    //创建菜单栏
    QMenuBar * bar=menuBar();
    //创建开始菜单
    QMenu * stratmenu=bar->addMenu("开始");
    //创建退出菜单项
    QAction * quitaction=stratmenu->addAction("退出");
    //点击退出，实现退出
    connect(quitaction,&QAction::triggered,[=](){
        this->close();
    });
    QSound * choosesound=new QSound(":/res/TapButtonSound.wav",this);
     QSound * backsound=new QSound(":/res/BackButtonSound.wav",this);
    //返回按钮
MyPushbutton *backbtn=new MyPushbutton(":/res/BackButton.png",":/res/BackButtonSelected.png");
backbtn->setParent(this);
backbtn->move(this->width()-backbtn->width(),this->height()-backbtn->height());
//点击返回
connect(backbtn,&MyPushbutton::clicked,[=](){
//告诉主场景，我返回了，主场景监听chooselevelsence的返回按钮
    //延时返回
    backsound->play();
    QTimer::singleShot(700,this,[=](){
        emit this->ChooseSceneBack();
    });

});
//创建选择关卡的按钮
for(int i=0;i<20;i++){
    MyPushbutton * menubtn=new MyPushbutton(":/res/LevelIcon.png");
    menubtn->setParent(this);
    menubtn->move(45+i%4*120,140+i/4*120);
    //QLabel 是 Qt 框架中用于显示文本或图像的小部件
    //监听每个按钮的事件
    connect(menubtn,&MyPushbutton::clicked,[=](){

        choosesound->play();
        QString str=QString("您选择的是第%1关").arg(i+1);
        qDebug()<<str;

        //进入到游戏场景
        this->hide();
        play=new PlaySence(i+1);
        play->setGeometry(this->geometry());
        play->show();

       // 进入关卡后play页面按了返回之后
        connect(play,&PlaySence::ChooseSceneBack,[=](){
            this->setGeometry(play->geometry());
            this->show();
            delete play;
            play=NULL;
        });
    });
   QLabel *label=new QLabel;
   label->setParent(this);
   label->setFixedSize(menubtn->width(),menubtn->height());
   //QString::number(i+1) 是一个将整数转换为 QString 类型的函数调用
   label->setText(QString::number(i+1));
   label->move(45+i%4*120,140+i/4*120);
   //设置文字水平居中和垂直区中
   label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
   //设置让鼠标进行穿透 51号属性
   label->setAttribute(Qt::WA_TransparentForMouseEvents);

}

}

void ChooseLevelScene::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  QPixmap pix;
     pix.load(":/res/OtherSceneBg.png");
  painter.drawPixmap(0,0,this->width(),this->height(),pix);
  //画背景上图标
   pix.load(":/res/Title.png");
   painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);

}
