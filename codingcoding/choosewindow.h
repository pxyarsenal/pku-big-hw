#ifndef CHOOSEWINDOW_H
#define CHOOSEWINDOW_H

#include <QLabel>
#include <QWidget>
#include "fullbutton.h"

class ChooseWindow : public QWidget
{
    Q_OBJECT
public:
    explicit ChooseWindow(QWidget *parent = nullptr);

    int map_choice = -1;
    void reset();

private:
    QLabel *background_label;
    FullButton *map1;
    FullButton *map2;
    FullButton *map3;
    FullButton *map4;
    FullButton *start;
    FullButton *to_exit;
    std::vector<FullButton*> map_list;

signals:
    void game_start(int choice);
    void back();
};

#endif // CHOOSEWINDOW_H
