#include "mainwindow.h"
#include "settlewindow.h"
#include "config.h"

#include <QString>

SettleWindow::SettleWindow(QWidget *parent)
    : QWidget{parent}
{
    setFixedSize(WIDTH, HEIGHT);

}

bool SettleWindow::win_or_not = false;

void SettleWindow::init(int mode, int _level_id)
{
    QString bg_src;
    level_id = _level_id;
    switch(mode)
    {
        case WIN: bg_src = ":/settlement/AC"; break;
        case HP_EMPTY: bg_src = ":/settlement/WA"; break;
        case OP_EMPTY: bg_src = ":/settlement/_LE"; break;
        case KEY_EMPTY: bg_src = ":/settlement/PE"; break;
        default: break;
    }

    background_label = new QLabel(this);
    background_label->setGeometry(0, 0, width(), height());
    QPixmap background(bg_src);
    background_label->setPixmap(background.scaled(size()));

    if(MainWindow::instory && mode == WIN){
        SettleWindow::win_or_not = true;
        restart = new FullButton(":/button/start.png", "CONTINUE", this);
        restart->move(350, 500);
        connect(restart, &FullButton::clicked, this, [=]{
            emit settle_to_dialog();
        });
        qDebug()<<map_id;

    }
    else{
        restart = new FullButton(":/button/start.png", "RESTART", this);
        restart->move(350, 500);
        connect(restart, &FullButton::clicked, this, [=]{
            emit Restarted(level_id);
        });
    }

    to_exit = new FullButton(":/button/exit.png", "MAIN MENU", this);
    to_exit->move(640, 500);
    connect(to_exit, &FullButton::clicked, this, [=]{
        MainWindow::instory=false;
        emit BacktoMain();
    });
    qDebug()<<map_id;
}
