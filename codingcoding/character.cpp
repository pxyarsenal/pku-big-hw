#include "character.h"
#include "config.h"

#include <QGraphicsScene>
#include <QDebug>

Character::Character(int _hp, int _steps_left, QGraphicsScene *parent)
    : QObject(), QGraphicsPixmapItem(),energy(0), key(false)
{
    hp = _hp;
    steps_left = _steps_left;
    QPixmap pixmap(":/character/stand.png");
    QPixmap scaled_pixmap = pixmap.scaled(CUBE_SIZE/2, CUBE_SIZE);
    setPixmap(scaled_pixmap);
    setParent(parent);

    change_timer = new QTimer(this);
    change_timer->setInterval(700);
}

int Character::showHp(){return hp;}
int& Character::showStepsLeft(){return steps_left;}
int Character::posx(){return pos[0];}
int Character::posy(){return pos[1];}
//bool Character::checkInBoard(){return (pos[0]>=0)&&(pos[0]<cur_map_w)&&(pos[1]>=0)&&(pos[1]<cur_map_h);}
bool Character::ownAKey(){return key;}
void Character::hpDecrease(){hp-=1;}
void Character::hpIncrease(){hp+=1;}
void Character::stepsLeftDecrease(){steps_left-=1;}
void Character::stepsLeftIncrease(){steps_left+=1;}
//inline void Character::turnLeft(){pos[0]-=1;}
//inline void Character::turnRight(){pos[0]+=1;}
//inline void Character::turnUp(){pos[1]-=1;}
//inline void Character::turnDown(){pos[1]+=1;}
void Character::getEnergy(){energy += 5;}
void Character::fallDown(){
    qDebug() << "oops!";
    QPixmap pixmap(":/character/fall.png");
    QPixmap scaled_pixmap = pixmap.scaled(CUBE_SIZE, CUBE_SIZE);
    setPixmap(scaled_pixmap);

    change_timer->stop();
    change_timer->setInterval(700);
    change_timer->start();
    connect(change_timer, &QTimer::timeout, this, &Character::stand_up);

}

void Character::push(QString img_path){
    QPixmap pixmap(img_path);
    QPixmap scaled_pixmap = pixmap.scaled(CUBE_SIZE, CUBE_SIZE);
    setPixmap(scaled_pixmap);

    change_timer->stop();
    change_timer->setInterval(700);
    change_timer->start();
    connect(change_timer, &QTimer::timeout, this, &Character::stand_up);
}

void Character::mmove(QString img_path){
    QPixmap pixmap(img_path);
    QPixmap scaled_pixmap = pixmap.scaled(CUBE_SIZE, CUBE_SIZE);
    setPixmap(scaled_pixmap);

    change_timer->stop();
    change_timer->setInterval(700);
    change_timer->start();
    connect(change_timer, &QTimer::timeout, this, &Character::stand_up);
}

void Character::stand_up(){
    QPixmap ppixmap(":/character/stand.png");
    QPixmap scaled_ppixmap = ppixmap.scaled(CUBE_SIZE / 2, CUBE_SIZE);
    setPixmap(scaled_ppixmap);
}

void Character::set_map_pos(int x, int y)
{
    pos[0] = x;
    pos[1] = y;
}

void Character::interact(gameObject*& x){

    int dx=0,dy=0;
    switch(x->type){
    case 1:{
        dx = -CUBE_SIZE*(pos[0] - x->posx);
        dy = -CUBE_SIZE*(pos[1]- x->posy);
        pos[0] = x->posx;
        pos[1] = x->posy;
        break;
    }
    case 2:{
        //spike* y = (spike*)(x);
        dx = -CUBE_SIZE*(pos[0] - x->posx);
        dy = -CUBE_SIZE*(pos[1]- x->posy);
        pos[0] = x->posx;
        pos[1] = x->posy;
        //if(!y->sleep())hpDecrease();
        hpDecrease();
        break;
    }
    case 3:{
        fallDown();
        break;
    }
    case 4:{
        dx = -CUBE_SIZE*(pos[0] - x->posx);
        dy = -CUBE_SIZE*(pos[1]- x->posy);
        pos[0] = x->posx;
        pos[1] = x->posy;
        break;
    }
    case 5:{
        pickKey();
        dx = -CUBE_SIZE*(pos[0] - x->posx);
        dy = -CUBE_SIZE*(pos[1]- x->posy);
        pos[0] = x->posx;
        pos[1] = x->posy;
        //key vanish
        stepsLeftDecrease();
        delete x;
        x = nullptr;
        //重新new出来放在game里面实现，因为不知道this是什么
        key = true;
        break;
    }
    case 6:{
        hpIncrease();
        stepsLeftIncrease();
        getEnergy();
        dx = -CUBE_SIZE*(pos[0] - x->posx);
        dy = -CUBE_SIZE*(pos[1]- x->posy);
        pos[0] = x->posx;
        pos[1] = x->posy;
        delete x;
        x = nullptr;

        break;
    }
    case 7:{
        hpDecrease();
        if(hp>0){
            dx = -CUBE_SIZE*(pos[0] - x->posx);
            dy = -CUBE_SIZE*(pos[1]- x->posy);
            pos[0] = x->posx;
            pos[1] = x->posy;
        }
        delete x;
        x = nullptr;

        break;
    }
    case 9:{
        if(hp>0){
            dx = -CUBE_SIZE*(pos[0] - x->posx);
            dy = -CUBE_SIZE*(pos[1]- x->posy);
            pos[0] = x->posx;
            pos[1] = x->posy;

        }
        break;
    }
    default:break;
    }
    if (dy == -CUBE_SIZE){
        mmove(":/character/left.png");
    }
    else if (dy == CUBE_SIZE){
        mmove(":/character/right.png");
    }
    moveBy(dy, dx);
}
