#ifndef MYCOIN_H
#define MYCOIN_H
#include <QTimer>
#include <QPushButton>
#include<QMouseEvent>
class MyCoin : public QPushButton
{
    Q_OBJECT
public:
   // explicit MyCoin(QWidget *parent = nullptr);
    //传入的金币路径还是银币路径
    //金币属性
    int posx,posy;
    int flag;//正面或者反面
    //改变标志的方法
    void changeFlag();
    QTimer *timer1;
    QTimer *timer2;
    int min=1,max=8;
    bool isanimation =false;//执行动画标志
    bool iswin=false;//是否胜利，不符值系统会默认赋值
    //重写按下和释放
    void mousePressEvent(QMouseEvent *e);
     MyCoin(QString btnImg);
signals:

};

#endif // MYCOIN_H
