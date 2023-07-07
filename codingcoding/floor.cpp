#include "floor.h"
#include "config.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>

Floor::Floor(int _posx,int _posy):QGraphicsPixmapItem()
{
    posx = _posx;
    posy = _posy;

    QPixmap pixmap(":/background/floor.jpg");
    QPixmap scaled_pixmap = pixmap.scaled(CUBE_SIZE, CUBE_SIZE);
    setPixmap(scaled_pixmap);

}
Floor::~Floor(){

}
