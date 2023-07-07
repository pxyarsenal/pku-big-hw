#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
/*
 * 此类的功能是维护地图上的物品，便于与人物进行交互。
 * 位于background
 */
class gameObject:public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    gameObject(QGraphicsScene *parent = nullptr);
    int type;    //地图类型
    int posx;    //x坐标位置
    int posy;    //y坐标位置

    int reward;    //不同类型的地图的回复
    gameObject(int _type,int _posx,int _posy,int _reward, QGraphicsScene *parent = nullptr);
    ~gameObject();

};

class common_map: public gameObject{
public:
    common_map();
    common_map(int _type, int _posx, int posy, int _reward, QGraphicsScene *parent = nullptr);
};

class spike: public gameObject{
private:
    bool _sleep_;
public:
    spike();
    spike(int _type,int _posx,int _posy,int _reward, QGraphicsScene *parent = nullptr);
    bool sleep();
};

class unmoveable_wall: public gameObject{
public:
    unmoveable_wall();
    unmoveable_wall(int _type,int _posx,int _posy,int _reward, QGraphicsScene *parent = nullptr);
};

class moveable_wall:public gameObject{
public:
    moveable_wall();
    moveable_wall(int _type,int _posx,int _posy,int _reward, QGraphicsScene *parent = nullptr);
};

class keys:public gameObject{
public:
    keys();
    keys(int _type,int _posx,int _posy,int _reward, QGraphicsScene *parent = nullptr);
};

class treasure:public gameObject{
public:
    treasure();
    treasure(int _type,int _posx,int _posy,int _reward, QGraphicsScene *parent = nullptr);
};

class monster:public gameObject{
public:
    int hp;
    // int skill;
    monster();
    monster(int _type,int _posx,int _posy,int _reward, QGraphicsScene *parent = nullptr);

};

class gate:public gameObject{
public:
    gate();
    gate(int _type,int _posx,int _posy,int _reward, QGraphicsScene *parent = nullptr);

};

#endif // GAMEOBJECT_H
