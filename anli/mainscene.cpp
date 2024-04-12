#include "mainscene.h"
#include "ui_mainscene.h"
#include <QPainter>
#include<QPixmap>
#include<QDebug>
#include "mypushbutton.h"
#include<QTimer>
#include<QSound>//多媒体模块下的音效
MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);
    //设置主场景
    //设置页面固定大小
    setFixedSize(520,888);
    //设置图标
    setWindowIcon(QIcon(":/res/Coin0001.png"));
    //设置标题
    setWindowTitle("翻金币主场景");
    //退出按钮,触发 ui->actionquit 时关闭当前窗口
    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });
   // 准备开始按钮的音效
    QSound *stratsound=new QSound(":/res/TapButtonSound.wav",this);

    //开始按钮
    MyPushbutton * startbtn=new MyPushbutton(":/res/MenuSceneStartButton.png");
    //把按钮放到 窗口中
    startbtn->setParent(this);
    startbtn->move(this->width()*0.5-startbtn->width()*0.5,this->height()*0.7);
    //实例化选择关卡场景
    choosesence=new ChooseLevelScene;
    //监听选择关卡返回的信号
    connect(choosesence,&ChooseLevelScene::ChooseSceneBack,[=](){
        this->setGeometry(choosesence->geometry());
        choosesence->hide();
        this->show();//重新显示主场景
    });
    connect(startbtn,&MyPushbutton::clicked,[=](){
        qDebug()<<"点击了开始按钮";
        //播放音效
        stratsound->play();

      startbtn->zoom1();
      startbtn->zoom2();
      QTimer::singleShot(500,this,[=](){
          //设置场景位置
          //将当前窗口或控件的几何属性设置为与其父窗口相同，以实现一致的位置和大小。
          choosesence->setGeometry(this->geometry());
          //进入并显示到选择关卡场景，自身隐藏
           this->hide();

           choosesence->show();


      });


    });

}
//可以实现自定义的绘图逻辑，例如绘制自定义的图形、文字等。
void MainScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    //加载图片，整个大背景图
    pix.load(":/res/PlayLevelSceneBg.png");
    //画家画图片
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
   //画背景上图标
    pix.load(":/res/Title.png");
     //缩放原始图
    pix=pix.scaled(pix.width()*0.8,pix.height()*0.8);
    painter.drawPixmap(25,25,pix);
}

MainScene::~MainScene()
{
    delete ui;
}
