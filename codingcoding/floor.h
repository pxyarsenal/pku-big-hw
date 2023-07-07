#ifndef FLOOR_H
#define FLOOR_H
/*
 * 此类的作用是维护游戏时放在底部的地板
 */
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
class Floor:public QGraphicsPixmapItem
{
public:
    int posx;
    int posy;
    Floor(int _posx,int _posy);
    ~Floor();

};

#endif // FLOOR_H
