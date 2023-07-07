#ifndef CHARACTER_H
#define CHARACTER_H

#include "gameobject.h"
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QKeyEvent>
#include <QTimer>

class Character : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    int hp;           //血量
    int steps_left;    //所剩步数
    int energy;        //能量条，用于释放技能
    int pos[2];        //当前位置，与map对应
    bool key;         //是否有钥匙，判断可否通关

public:
    explicit Character(int _hp, int _steps_left, QGraphicsScene *parent = nullptr);

    int showHp();
    int& showStepsLeft();
    int posx();
    int posy();
    void set_map_pos(int x, int y);
    //bool checkInBoard();
    bool ownAKey();   //是否有钥匙，判断可否通关
    void hpDecrease();
    void hpIncrease();
    void stepsLeftDecrease();
    void stepsLeftIncrease();
    //    inline void turnLeft();
    //    inline void turnRight();
    //    inline void turnUp();
    //    inline void turnDown();
    void getEnergy();
    void pickKey(){key = true;}
    void interact(gameObject*& x);
    void fallDown();  //碰墙后摔倒
    void die();   //血量《=0触发
    void lose();  //步数《=0触发
    void skill();
    void push(QString img_path);
    void mmove(QString img_path);

    QTimer *change_timer;

signals:

public slots:
    void stand_up();
};

#endif // CHARACTER_H
