#ifndef DIALOGWINDOW_H
#define DIALOGWINDOW_H

#include <QLabel>
#include <QObject>
#include <QWidget>
#include <txtshow.h>
#include "fullbutton.h"

class DialogWindow:public QWidget
{
    Q_OBJECT
public:
    int order;
    QLabel *background_label;
    FullButton *choice1;
    FullButton *choice2;
    explicit DialogWindow(QWidget *parent = nullptr);
    void startDialog();
    void BacktoGame();
    //void keyPressEvent(QKeyEvent* event);
    void mousePressEvent(QMouseEvent *ev);
};

#endif // DIALOGWINDOW_H
