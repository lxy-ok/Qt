#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H
#include<QPushButton>
#include<QMouseEvent>
//表示定义了一个类 MyPushbutton，它是 QPushButton 类的子类（或称为派生类）。
//在 C++ 中，冒号 : 后面跟着的是该类的基类（或称为父类）
class MyPushbutton : public  QPushButton
{
    Q_OBJECT
public:
    //explicit MyPushbutton(QWidget *parent = nullptr);
    //构造函数，正常显示图片，按下后显示的图片
  MyPushbutton(QString normalImg,QString pressImg="");
  //正常的路径，按下后的路径
  QString normalIngPath;
  QString pressImgPath;
  //弹跳特效,向下，向上
  void zoom1();
void zoom2();
//重写按钮按下和释放事件
 void mousePressEvent(QMouseEvent *e);
 void mouseReleaseEvent(QMouseEvent *e);
signals:

};

#endif // MYPUSHBUTTON_H
