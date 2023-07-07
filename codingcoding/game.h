#ifndef GAME_H
#define GAME_H

#include <QGraphicsScene>
#include <QLabel>
#include "floor.h"
#include "gameobject.h"
#include "character.h"
#include <QGraphicsTextItem>
#include <QLabel>


class Game : public QGraphicsScene
{
    Q_OBJECT
public:
    Game();
    void init(int id);

    friend class Character;
    void keyPressEvent(QKeyEvent *event);

    bool isgoing = false;
    int level_id;

    static bool iffinish;

private:
    int level[11][11]{};
    Floor *groundFloor[11][11]{};
    gameObject *level_map[11][11]{};
    Character* character;
    QGraphicsPixmapItem * StatusPic;
    QGraphicsTextItem* CharacterHP;
    QGraphicsTextItem* CharacterStep;

signals:
    void isPaused(int id);
    void isResumed();
    void toSettlement(int mode, int id);

};

#endif // GAME_H
