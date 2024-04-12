#ifndef PLAYSENCE_H
#define PLAYSENCE_H
#include<QLabel>
#include <QMainWindow>
#include <mycoin.h>
#include<QTime>
#include<QTimer>
class PlaySence : public QMainWindow
{
    Q_OBJECT
public:
  //  explicit PlaySence(QWidget *parent = nullptr);
PlaySence(int levelnum);
int levelindex;//内部成员属性，记录所选关卡
//重写绘画事件
void paintEvent(QPaintEvent *);
void updateTimer();
QLabel *label; // 用于显示计时器的 QLabel

   QTime elapsedTime; // 经过的时间
int gamearray[4][4];//二维数组，维护每个关卡的具体数据
MyCoin * coinbtn[4][4];
 bool iswin;//是否胜利
signals:
//写一个自定义的信号，告诉选关场景返回
void ChooseSceneBack();//自定义信号只需要声明，不需要实现
};

#endif // PLAYSENCE_H
