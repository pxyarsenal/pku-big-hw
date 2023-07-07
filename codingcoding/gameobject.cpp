#include "gameobject.h"
#include "config.h"

#include <QRandomGenerator>

//此类为实现所有的地图事件
gameObject::gameObject(QGraphicsScene *parent)
{
    setParent(parent);
}

gameObject::gameObject(int _type,int _posx,int _posy,int _reward, QGraphicsScene *parent):QObject(), QGraphicsPixmapItem(){
    this->type = _type;
    this->posx = _posx;
    this->posy = _posy;
    this->reward = _reward;
    setParent(parent);
}

common_map::common_map(int _type, int _posx, int _posy, int _reward, QGraphicsScene *parent):gameObject(_type, _posx, _posy, _reward, parent){

}

spike::spike(int _type,int _posx,int _posy,int _reward, QGraphicsScene *parent):gameObject(_type, _posx,_posy,_reward, parent){
    QPixmap pixmap(":/landscale/spike.png");
    QPixmap scaled_pixmap = pixmap.scaled(CUBE_SIZE, CUBE_SIZE);
    setPixmap(scaled_pixmap);
}

unmoveable_wall::unmoveable_wall(int _type,int _posx,int _posy,int _reward, QGraphicsScene *parent):gameObject(_type, _posx,_posy,_reward, parent){
    QPixmap pixmap(":/landscale/wall.jpg");
    QPixmap scaled_pixmap = pixmap.scaled(CUBE_SIZE, CUBE_SIZE);
    setPixmap(scaled_pixmap);
}

moveable_wall::moveable_wall(int _type,int _posx,int _posy,int _reward, QGraphicsScene *parent):gameObject(_type, _posx,_posy,_reward, parent){
    QPixmap pixmap(":/landscale/table.png");
    QPixmap scaled_pixmap = pixmap.scaled(CUBE_SIZE, CUBE_SIZE);
    setPixmap(scaled_pixmap);
}

keys::keys(int _type,int _posx,int _posy,int _reward, QGraphicsScene *parent):gameObject(_type, _posx,_posy,_reward, parent){
    QPixmap pixmap(":/landscale/key.png");
    QPixmap scaled_pixmap = pixmap.scaled(CUBE_SIZE, CUBE_SIZE);
    setPixmap(scaled_pixmap);
}

treasure::treasure(int _type,int _posx,int _posy,int _reward, QGraphicsScene *parent):gameObject(_type, _posx,_posy,_reward, parent){

}

monster::monster(int _type,int _posx,int _posy,int _reward, QGraphicsScene *parent):gameObject(_type, _posx,_posy,_reward, parent){
    int randomInt = QRandomGenerator::global()->bounded(3);
    QString SRC;
    switch(randomInt){
        case 0: SRC = ":/character/ljy.png"; break;
        case 1: SRC = ":/character/zqj.png"; break;
        case 2: SRC = ":/character/gw.png"; break;
        default: break;
    }

    QPixmap pixmap(SRC);
    QPixmap scaled_pixmap = pixmap.scaled(CUBE_SIZE, CUBE_SIZE);
    setPixmap(scaled_pixmap);
}

gate::gate(int _type,int _posx,int _posy,int _reward, QGraphicsScene *parent):gameObject(_type, _posx,_posy,_reward, parent){
    QPixmap pixmap(":/landscale/gate.jpg");
    QPixmap scaled_pixmap = pixmap.scaled(CUBE_SIZE, CUBE_SIZE);
    setPixmap(scaled_pixmap);
}
//类的初始化构造

//数值：数组的第一维是x,第二维是y
//拿到一个treasure奖励1，踩到地磁奖励-1

bool spike::sleep(){return _sleep_;}

gameObject::~gameObject(){

}
