#ifndef MAINSCENE_H
#define MAINSCENE_H
#include "chooselevelscene.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainScene; }
QT_END_NAMESPACE

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = nullptr);
    ~MainScene();
void  paintEvent(QPaintEvent *);
ChooseLevelScene * choosesence=NULL;
private:
    Ui::MainScene *ui;
};
#endif // MAINSCENE_H
