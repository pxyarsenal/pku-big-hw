#ifndef PAUSEWINDOW_H
#define PAUSEWINDOW_H

#include "fullbutton.h"
#include "game.h"

#include <QWidget>
#include <QGraphicsRectItem>
#include <QPainter>

class PauseWindow : public QWidget
{
    Q_OBJECT
public:
    explicit PauseWindow(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    void init(int _level_id);
    int level_id;

signals:
    void Resumed();
    void BacktoMain();
    void Restarted(int id);

private:
    FullButton *resume;
    FullButton *to_exit;
    FullButton *restart;
};

#endif // PAUSEWINDOW_H
