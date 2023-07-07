#include "pausewindow.h"
#include "config.h"

#include <QGraphicsView>

PauseWindow::PauseWindow(QWidget *parent)
    : QWidget{parent}
{
    setFixedSize(WIDTH, HEIGHT);

}

void PauseWindow::init(int _level_id)
{
    int level_id = _level_id;
    setFixedSize(WIDTH, HEIGHT);

    resume = new FullButton(":/button/start.png", "RESUME", this);
    resume->move(350, 400);
    connect(resume, &FullButton::clicked, this, [=]{
        emit Resumed();
    });

    to_exit = new FullButton(":/button/exit.png", "MAIN MENU", this);
    to_exit->move(640, 400);
    connect(to_exit, &FullButton::clicked, this, [=]{
        emit BacktoMain();
    });

    restart = new FullButton(":/button/start.png", "RESTART", this);
    restart->move(480, 200);
    connect(restart, &FullButton::clicked, this, [=]{
        emit Restarted(level_id);
    });
}

void PauseWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(Qt::black, 3));
    painter.setBrush(Qt::gray);
    painter.drawRoundedRect(rect().center().x() - 300, rect().center().y() - 200, 600, 400, 50, 50);
}
