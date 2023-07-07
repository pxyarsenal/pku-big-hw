#include "game.h"
#include "config.h"
#include "floor.h"
#include "musicloader.h"
#include <QDebug>
#include <QLabel>
#include <QFont>


bool Game::iffinish = false;

Game::Game()
{
}

void Game::init(int id)
{
    clear();
    setSceneRect(0, 0, WIDTH, HEIGHT);

    isgoing = true;
    level_id = id;


    //for this id, the corresponding map
    for (int i = 0; i < 11; i++){
        for (int j = 0; j < 11; j++)
            level[i][j] = ALL_MAPS[id][i][j];
    }

    //for this id, the corresponding background
    QImage image (MAP_BG_SRC[id]);
    setBackgroundBrush(QBrush(QImage(image).scaled(WIDTH, HEIGHT)));

    //adding game item to the scene
    int start_j = 0, start_i = 0;
    for(int i=0;i<11;i++){
        for(int j=0;j<11;j++){
            if (level[i][j] == 0)
                continue;

            groundFloor[i][j] = new Floor(i,j);
            addItem(groundFloor[i][j]);
            groundFloor[i][j]->setPos(200 + CUBE_SIZE*j, 20 + CUBE_SIZE*i);

            if(level[i][j]==1) level_map[i][j] = new common_map(COMMON_MAP, i, j, 0, this);
            else if(level[i][j]==2) level_map[i][j] = new spike(SPIKE,i,j,-1, this);
            else if(level[i][j]==3) level_map[i][j] = new unmoveable_wall(UNMOVEABLE_WALL,i,j,0, this);
            else if(level[i][j]==4) level_map[i][j] = new moveable_wall(MOVEABLE_WALL,i,j,0, this);
            else if(level[i][j]==5) level_map[i][j] = new keys(KEYS,i,j,0, this);
            else if (level[i][j]==6) level_map[i][j] = new treasure(TREASURE,i,j,1, this);
            else if(level[i][j]==7) level_map[i][j] = new monster(MONSTER,i,j,-1, this);
            else if (level[i][j] == 8){
                level_map[i][j] = new common_map(COMMON_MAP, i, j, 0, this);
                start_j = j; start_i = i;
            }else if(level[i][j] == 9) level_map[i][j] = new gate(GATE,i,j,0,this);

            if (level_map[i][j]){
                addItem(level_map[i][j]);
                level_map[i][j]->setPos(200 + CUBE_SIZE*j, 20 + CUBE_SIZE*i);
            }
        }
    }

    //adding character item to the scene
    character = new Character(MAP_CHAR_INFO[id][1], MAP_CHAR_INFO[id][0]);
    addItem(character);
    character->set_map_pos(start_i, start_j);
    character->setPos(200 + CUBE_SIZE * start_j + CUBE_SIZE / 4, 20 + CUBE_SIZE * start_i);

    //character status
    StatusPic = new QGraphicsPixmapItem;
    QPixmap background(":/background/status.png");
    StatusPic->setPixmap(background.scaled(QSize(200,120)));
    addItem(StatusPic);
    StatusPic->setPos(30,30);

    QFont font;
    font.setPointSize(18);
    font.setFamily("Chiller");

    CharacterHP = new QGraphicsTextItem;
    CharacterHP->setPlainText(QString("Health Points: ") + QString::number(character->showHp()));
    CharacterHP->setDefaultTextColor(Qt::black);
    CharacterHP->setFont(font);
    addItem(CharacterHP);
    CharacterHP->setPos(60,45);

    CharacterStep = new QGraphicsTextItem;
    CharacterStep->setPlainText(QString("MOVES: ") + QString::number(character->showStepsLeft()));
    CharacterStep->setDefaultTextColor(Qt::black);
    CharacterStep->setFont(font);
    addItem(CharacterStep);
    CharacterStep->setPos(70,75);

}

void Game::keyPressEvent(QKeyEvent *event)
{
    if (isgoing)
    {
        if (event->key() == Qt::Key_Escape)
        {
            emit isPaused(level_id);
            return;
        }
        if (character){
            int tar_row = character->posx(),tar_col = character->posy();
            int direction=0;
            bool operated = true;
            switch (event->key())
            {
            case Qt::Key_Left:tar_col -= 1; direction=1; break;
            case Qt::Key_Right:tar_col +=1; direction=2; break;
            case Qt::Key_Up:tar_row -=1; direction=3; break;
            case Qt::Key_Down: tar_row+=1; direction=4; break;
            default: operated = false; break;
            }
            if (operated)
                character->stepsLeftDecrease();
            CharacterStep->setPlainText(QString("MOVES: ") + QString::number(character->showStepsLeft()));
            if(character->showStepsLeft()<0){iffinish = true;emit toSettlement(OP_EMPTY, level_id);}

            if(level_map[tar_row][tar_col]->type==4){
                gameObject* checkIfMoveable;
                int checkPosRow,checkPosCol;
                switch(direction){
                    case 1: checkIfMoveable = level_map[tar_row][tar_col-1]; checkPosRow = tar_row;checkPosCol = tar_col-1;break;
                    case 2: checkIfMoveable = level_map[tar_row][tar_col+1]; checkPosRow = tar_row;checkPosCol = tar_col+1;break;
                    case 3: checkIfMoveable = level_map[tar_row-1][tar_col]; checkPosRow = tar_row-1;checkPosCol = tar_col;break;
                    case 4: checkIfMoveable = level_map[tar_row+1][tar_col]; checkPosRow = tar_row+1;checkPosCol = tar_col;break;
                }
                if(checkIfMoveable->type==1){
                    //character push
                    switch(direction){
                        case 1: character->push(":/character/push_left.png"); break;
                        case 2: character->push(":/character/push_right.png"); break;
                        case 3: character->push(":/character/push_up.png"); break;
                        case 4: character->push(":/character/push_down.png"); break;
                    }

                    delete level_map[checkPosRow][checkPosCol];
                    delete level_map[tar_row][tar_col];
                    level_map[checkPosRow][checkPosCol] = new moveable_wall(MOVEABLE_WALL, checkPosRow, checkPosCol, 0, this);
                    level_map[tar_row][tar_col] = new common_map(COMMON_MAP, tar_row, tar_col, 0, this);

                    addItem(level_map[checkPosRow][checkPosCol]);
                    level_map[checkPosRow][checkPosCol]->setPos(200 + CUBE_SIZE*checkPosCol, 20 + CUBE_SIZE*checkPosRow);
                    addItem(level_map[tar_row][tar_col]);
                    level_map[tar_row][tar_col]->setPos(200 + CUBE_SIZE*tar_col, 20 + CUBE_SIZE*tar_row);
                }else{

                    switch(direction){
                        case 1: tar_col+=1;break;
                        case 2: tar_col-=1;break;
                        case 3: tar_row+=1;break;
                        case 4: tar_row-=1;break;
                    }
                        //角色跌倒;
                    character->fallDown();
                }
            }else if(level_map[tar_row][tar_col]->type==9){
                if(character->ownAKey()==true)emit toSettlement(WIN, level_id);
                else emit toSettlement(KEY_EMPTY, level_id);
            }

            character->interact(level_map[tar_row][tar_col]);
            if(level_map[tar_row][tar_col]==nullptr){
                qDebug() << "key vanished!";
                level_map[tar_row][tar_col] = new common_map(COMMON_MAP, tar_row, tar_col, 0, this);
            }
            CharacterHP->setPlainText(QString("Health Points: ") + QString::number(character->showHp()));
            if(character->showHp()<=0) emit toSettlement(HP_EMPTY, level_id);
        }
    }
    else
    {
        if (event->key() == Qt::Key_Escape)
        {
            emit isResumed();
            return;
        }
    }
}
