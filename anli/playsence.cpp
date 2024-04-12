#include "playsence.h"
#include "mypushbutton.h"
#include<QDebug>
#include<QPainter>
#include<QMenuBar>
#include<QPixmap>
#include<QTimer>
#include<QLabel>
#include "dataconfig.h"
#include<QPropertyAnimation>
#include<QSound>
//PlaySence::PlaySence(QWidget *parent) : QMainWindow(parent)
//{

//}
PlaySence::PlaySence(int levelnum)
{   QString str=QString("进入第%1关").arg(levelnum);
    qDebug()<<str;
    this->levelindex=levelnum;
    //初始化游戏场景
    //设置固定大小
    this->setFixedSize(520,888);
    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置标题
    this->setWindowTitle("翻金币场景");
    //创建菜单栏
    QMenuBar * bar=menuBar();
    //创建开始菜单
    QMenu * startmenu=bar->addMenu("开始");
    //创建退出
    QAction * quitaction=startmenu->addAction("退出");
    //点击退出实现退出游戏
    connect(quitaction,&QAction::triggered,[=](){
        this->close();
    });
     QSound *backsound=new QSound(":/res/BackButtonSound.wav",this);
    QSound *flipsound=new QSound(":/res/ConFlipSound.wav",this);
    QSound *winsound=new QSound(":/res/LevelWinSound.wav",this);
    //返回按钮
MyPushbutton *backbtn=new MyPushbutton(":/res/BackButton.png",":/res/BackButtonSelected.png");
backbtn->setParent(this);
backbtn->move(this->width()-backbtn->width(),this->height()-backbtn->height());
//点击返回
connect(backbtn,&MyPushbutton::clicked,[=](){
//告诉上一个选关场景，我返回了，选关场景监听返回按钮
    //延时返回
    backsound->play();
    QTimer::singleShot(700,this,[=](){
        emit this->ChooseSceneBack();//发送信号
    });

});
  //左下角显示当前关卡数
  QLabel * label=new QLabel();
  label->setParent(this);
  QFont font;
  font.setFamily("华文新魏");
   font.setPointSize(20);
   QString stri=QString("LEVEL: %1").arg(levelnum);
   //将字体设置到标签控件中
   label->setFont(font);
   label->setText(stri);
   label->setGeometry(30,this->height()-70,150,120);

   // 创建 QLabel 来显示计时器

         label = new QLabel("00:00:00", this);
         QFont font2;
         font.setFamily("华文新魏");
         font.setPointSize(20);
         label->setFont(font2);
         label->setGeometry(this->width() - 450, 250, 180, 30);
         // 创建 QTimer 用于更新计时器
         QTimer* timer2 = new QTimer(this);
         connect(timer2, &QTimer::timeout, this, &PlaySence::updateTimer);
                 timer2->start(1000); // 每隔一秒触发一次 timeout 信号


   //初始化每个关卡的二维数组
   dataConfig config;
   for(int i=0;i<4;i++)
    for(int j=0;j<4;j++){
this->gamearray[i][j] = config.mData[this->levelindex][i][j];

      }
   //胜利图片显示
   QLabel *winlabel=new QLabel();
   QPixmap tempix;
   tempix.load(":/res/LevelCompletedDialogBg.png");
   winlabel->setGeometry(0,0,tempix.width(),tempix.height());
   winlabel->setPixmap(tempix);
   winlabel->setParent(this);
   winlabel->move((this->width()-tempix.width())*0.5,-this->height());

   //进入关卡中金币下面的背景图
   for(int i=0;i<4;i++){
       for(int j=0;j<4;j++)
   {    QPixmap pix = QPixmap(":/res/BoardNode.png");
           QLabel* label = new QLabel;
           label->setScaledContents(true);
           label->setGeometry(0,0,pix.width()*1.2,pix.height()*1.2);

           label->setPixmap(pix);
           label->setParent(this);
           label->move(137+i*60,312+j*60);

           //创建金币
              QString str2;
              if(this->gamearray[i][j])
              {
                  str2=":/res/Coin0001.png";
              }
              else{
                   str2=":/res/Coin0008.png";
              }
       //setPixmap() 是 QLabel 类的一个成员函数，用于设置标签的图像内容
       MyCoin * coin=new MyCoin(str2);
       coin->setParent(label);//这个不是this
          coin->move(i*3,j*3+1);
       //给金币属性赋值
       coin->posx=i;
       coin->posy=j;
      coin->flag=this->gamearray[i][j];
       //金币放到二维数组里面，维护
       coinbtn[i][j]=coin;
       //点击金币，进行翻转
       connect(coin,&MyCoin::clicked,[=](){
           flipsound->play();
           //点击某个按钮的瞬间，把所有按钮禁用掉，防止迅速又去点其他的按钮
           for(int i=0;i<4;i++)
               for(int j=0;j<4;j++){
                   this->coinbtn[i][j]->iswin=true;
               }
         coin->changeFlag();
           this->gamearray[i][j]=this->gamearray[i][j]==0?1:0;
          // 翻转周围
           QTimer::singleShot(300,this,[=](){
               if(coin->posx+1<=3){
                   coinbtn[coin->posx+1][coin->posy]->changeFlag();
      this->gamearray[coin->posx+1][coin->posy]=this->gamearray[coin->posx+1][coin->posy]==0?1:0;
               }
               if(coin->posx-1>=0){
                   coinbtn[coin->posx-1][coin->posy]->changeFlag();
      this->gamearray[coin->posx-1][coin->posy]=this->gamearray[coin->posx-1][coin->posy]==0?1:0;
               }
               if(coin->posy+1<=3){
                   coinbtn[coin->posx][coin->posy+1]->changeFlag();
      this->gamearray[coin->posx][coin->posy+1]=this->gamearray[coin->posx][coin->posy+1]==0?1:0;
               }
               if(coin->posy-1>=0){
                   coinbtn[coin->posx][coin->posy-1]->changeFlag();
      this->gamearray[coin->posx][coin->posy-1]=this->gamearray[coin->posx][coin->posy-1]==0?1:0;
               }
               for(int i=0;i<4;i++)
                   for(int j=0;j<4;j++){
                       this->coinbtn[i][j]->iswin=false;
                   }




               //判断是否胜利
               this->iswin=true;
               for(int i=0;i<4;i++)
                   for(int j=0;j<4;j++)
                   {
                       if(coinbtn[i][j]->flag==0) {this->iswin=false; break;}

                   }
               if(this->iswin=true){
                   qDebug()<<"胜利";
                   winsound->play();
                   for(int i=0;i<4;i++)
                       for(int j=0;j<4;j++){
                           coinbtn[i][j]->iswin=true;
                       }
               }

               //胜利的图片移动下来
               QPropertyAnimation *animation=new QPropertyAnimation(winlabel,"geometry");

               //设置时间间隔
                animation->setDuration(1000);
               //设置开始位置
                animation->setStartValue(QRect(winlabel->x(),winlabel->y(),winlabel->width(),winlabel->height()));
                //设置结束位置
                animation->setEndValue(QRect(winlabel->x(),winlabel->y()+1050,winlabel->width(),winlabel->height()));
                //设置缓和曲线
                animation->setEasingCurve(QEasingCurve::OutBounce);
                 //执行动画
                animation->start();
           });

       });

   }}

}

void PlaySence::paintEvent(QPaintEvent *)
{
    //背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //背景上面图片
    pix.load(":/res/Title.png");
    pix=pix.scaled(pix.width()*0.8,pix.height()*0.8);
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);
}

void PlaySence::updateTimer()
{
    // 更新计时器
            elapsedTime = elapsedTime.addSecs(1); // 每次增加一秒
            QString text = elapsedTime.toString("hh:mm:ss"); // 格式化显示时间
            label->setText("闯关计时：" + text); // 更新 QLabel 显示
}
