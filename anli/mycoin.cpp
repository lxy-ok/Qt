#include "mycoin.h"
#include<QDebug>

//MyCoin::MyCoin(QWidget *parent) : QPushButton(parent)
//{

//}


MyCoin::MyCoin(QString btnImg)
{   //QPixmap 类是用来处理图像的类。你可以使用 QPixmap 类来加载、显示和操作图像数据
    QPixmap pix;
    bool ret=pix.load(btnImg);
    if(!ret)
    {
        QString str=QString("图片%1加载失败").arg(btnImg);
        qDebug()<<str;
        return;
    }
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));
  timer1 =new QTimer(this);//new的话 这个用-> 指针
  timer2=new QTimer(this);
  //监听正面翻转反面的信号，并且翻转金币
  connect(timer1,&QTimer::timeout,[=](){
      QPixmap pix;
      QString str=QString(":/res/Coin000%1").arg(this->min++);
      pix.load(str);
      this->setFixedSize(pix.width(),pix.height());
      this->setStyleSheet("QPushButton{border:0px}");
      this->setIcon(pix);
      this->setIconSize(QSize(pix.width(),pix.height()));
      //如果翻完了，重置1
      if(this->min>this->max)
      {
          this->min=1;
          isanimation=false;
          timer1->stop();
      }
  });
  connect(timer2,&QTimer::timeout,[=](){
      QPixmap pix;
      QString str=QString(":/res/Coin000%1.png").arg(this->max--);
      pix.load(str);
      this->setFixedSize(pix.width(),pix.height());
      this->setStyleSheet("QPushButton{border:0px}");
      this->setIcon(pix);
      this->setIconSize(QSize(pix.width(),pix.height()));
      //如果翻完了，重置1
      if(this->min>this->max)
      {
          this->max=8;
          isanimation=false;
          timer2->stop();
      }
  });
}
void MyCoin::changeFlag()
{
    if(this->flag)
    { timer1->start(30);
        this->flag=0;
  isanimation=true;
    }
    else{
        timer2->start(30);
        this->flag=1;
        isanimation=true;
    }
}

void MyCoin::mousePressEvent(QMouseEvent *e)
{
    if(this->isanimation||this->iswin)
    {
        return;
    }
    else
      QPushButton::mousePressEvent(e);
}
