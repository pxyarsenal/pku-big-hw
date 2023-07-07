#include "choosewindow.h"
#include "config.h"

ChooseWindow::ChooseWindow(QWidget *parent)
    : QWidget{parent}
{
    setFixedSize(WIDTH, HEIGHT);

    //background
    background_label = new QLabel(this);
    background_label->setGeometry(0, 0, width(), height());
    QPixmap background(":/background/classroom.png");
    background_label->setPixmap(background.scaled(size()));
    background_label->setAlignment(Qt::AlignBottom);

    //button
    map1 = new FullButton(":/button/normal.png", "stage 1", this);
    map1->move(120, 120);
    map_list.push_back(map1);

    map2 = new FullButton(":/button/normal.png", "stage 2", this);
    map2->move(120, 350);
    map_list.push_back(map2);

    map3 = new FullButton(":/button/normal.png", "stage 3", this);
    map3->move(480, 150);
    map_list.push_back(map3);

    map4 = new FullButton(":/button/normal.png", "stage 4", this);
    map4->move(480, 380);
    map_list.push_back(map4);

    start = new FullButton(":/button/start.png", "START", this);
    start->move(800, 200);

    to_exit = new FullButton(":/button/exit.png", "MAIN MENU", this);
    to_exit->move(800, 500);

    //connect
    connect(to_exit, &FullButton::clicked, this, [=]{
        emit back();
    });
    connect(start, &FullButton::clicked, this, [=]{
        if (map_choice != -1)
            emit game_start(map_choice);
    });
    connect(map1, &FullButton::clicked, this, [=]{
        if (map_choice != -1){
            map_list[map_choice]->change_icon(":/button/normal.png");
        }
        map1->change_icon(":/button/picked.png");
        map_choice = 0;
    });
    connect(map2, &FullButton::clicked, this, [=]{
        if (map_choice != -1){
            map_list[map_choice]->change_icon(":/button/normal.png");
        }
        map2->change_icon(":/button/picked.png");
        map_choice = 1;
    });
    connect(map3, &FullButton::clicked, this, [=]{
        if (map_choice != -1){
            map_list[map_choice]->change_icon(":/button/normal.png");
        }
        map3->change_icon(":/button/picked.png");
        map_choice = 2;
    });
    connect(map4, &FullButton::clicked, this, [=]{
        if (map_choice != -1){
            map_list[map_choice]->change_icon(":/button/normal.png");
        }
        map4->change_icon(":/button/picked.png");
        map_choice = 3;
    });
}

void ChooseWindow::reset()
{
    map_choice = -1;
    for (FullButton* map: map_list){
        map->change_icon(":/button/normal.png");
    }
}
