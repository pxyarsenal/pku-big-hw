#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void keyPressEvent(QKeyEvent* event);
    static bool instory;


};

void dialogwindow_to_game();
void init_dialogwindow();
void settle_to_dialog();
static int map_id = 0;
#endif // MAINWINDOW_H
