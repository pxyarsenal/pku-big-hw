#include "mainwindow.h"
#include "config.h"
#include "fullbutton.h"
#include "choosewindow.h"
#include "game.h"
#include "pausewindow.h"
#include "settlewindow.h"
#include "dialogwindow.h"
#include "musicloader.h"

#include <QGraphicsView>
#include <QGraphicsEffect>
#include <QDebug>

QLabel *background_label;
FullButton *single;
FullButton *choose;
FullButton *to_exit;
ChooseWindow *choosewindow;
PauseWindow *pausewindow;
SettleWindow *settlewindow;
DialogWindow *dialogwindow;

Game *gamescene;


QGraphicsView *view;
QGraphicsBlurEffect *blur;

static MusicLoader *music;


int interface_mode = 0;

bool MainWindow::instory = false;

void init_choosewindow()
{
    interface_mode = _choosing_window;
    single->hide(); choose->hide(); to_exit->hide();
    choosewindow->reset();
    choosewindow->show();
}

void choosewindow_to_main()
{
    choosewindow->hide();
    single->show(); choose->show(); to_exit->show();
    interface_mode = _starting_window;
    MainWindow::instory=false;
    music->changeMusic(":/music/tuanzi.wav");
}

void game_started(int map)
{
    if (interface_mode == _settling_window)
        settlewindow->hide();
    else if (interface_mode == _pausing_window)
        pausewindow->hide();
    choosewindow->hide();
    gamescene->init(map);
    blur->setBlurRadius(0);
    view->setScene(gamescene);
    view->show();
    music->turnDownMusic();
    music->changeMusic(":/music/gamebgm.wav");
    interface_mode = _gaming_window;

}

void pause_now(int level_id)
{
    if (interface_mode == _gaming_window){
        pausewindow->init(level_id);
        pausewindow->show();
        blur->setBlurRadius(5);
        gamescene->isgoing = false;
        music->turnDownMusic();
        interface_mode = _pausing_window;
    }
}

void game_resumed()
{
    if (interface_mode == _pausing_window){
        pausewindow->hide();
        blur->setBlurRadius(0);
        gamescene->isgoing = true;
        interface_mode = _gaming_window;
        music->changeMusic(":/music/gamebgm.wav");
    }
}

void pausewindow_to_main()
{
    if (interface_mode == _pausing_window){
        pausewindow->hide();
        blur->setBlurRadius(0);
        view->hide();
        single->show(); choose->show(); to_exit->show();
        music->turnDownMusic();
        interface_mode = _starting_window;
        MainWindow::instory=false;
        music->changeMusic(":/music/tuanzi.wav");
    }
}

void init_settlewindow(int mode, int level_id)
{
    interface_mode = _settling_window;
    blur->setBlurRadius(5);
    settlewindow->init(mode, level_id);
    settlewindow->show();
}

void settlewindow_to_main()
{
    blur->setBlurRadius(0);
    view->hide();
    single->show(); choose->show(); to_exit->show();
    music->turnDownMusic();
    music->changeMusic(":/music/tuanzi.wav");
    settlewindow->hide();
    interface_mode = _starting_window;
    MainWindow::instory=false;
    qDebug()<<map_id;
}

void init_dialogwindow()
{
    //choosewindow->hide();
    if(map_id == 0){
        MainWindow::instory = true;
        single->hide();choose->hide();to_exit->hide();
        dialogwindow->show();
        dialogwindow->startDialog();
        dialogwindow_to_game();
    }
    else{
        MainWindow::instory = true;
        dialogwindow->hide();
        single->hide();choose->hide();to_exit->hide();
        qDebug()<<map_id;
        if(SettleWindow::win_or_not == false)game_started(map_id - 1);
        else {
            SettleWindow::win_or_not = false;
            game_started(map_id);
        }
    }
}

void dialogwindow_to_game(){
    if(map_id == 4){
        MainWindow::instory = false;
        dialogwindow->hide();
        single->show(); choose->show(); to_exit->show();
        interface_mode = _starting_window;
        map_id=0;
        dialogwindow->order =0;
        return;
    }
    dialogwindow->hide();
    game_started(map_id);
    dialogwindow->order++;
    map_id++;
    if(map_id>4)return;
}

void settle_to_dialog(){
    if(dialogwindow->order == 6){
        MainWindow::instory=false;
        dialogwindow->hide();
        single->show(); choose->show(); to_exit->show();
        interface_mode = _starting_window;
        map_id=0;
        dialogwindow->order =0;
        return;
    }
    dialogwindow->show();
    dialogwindow->startDialog();
    dialogwindow_to_game();
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //size, title, icon
    setFixedSize(WIDTH, HEIGHT);
    setWindowTitle("cheatPOJ");
    setWindowIcon(QIcon(":/icon/kick.ico"));
    interface_mode = _starting_window;

    //background
    background_label = new QLabel(this);
    background_label->setGeometry(0, 0, width(), height());
    QPixmap background(":/background/starting.jpg");
    background_label->setPixmap(background.scaled(size()));
    background_label->setAlignment(Qt::AlignBottom);

    gamescene = new Game();

    //view
    blur = new QGraphicsBlurEffect(this);
    blur->setBlurRadius(0);
    view = new QGraphicsView(this);
    view->setFixedSize(WIDTH, HEIGHT);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setGraphicsEffect(blur);
    view->hide();

    //turn on music
    QString dir=QCoreApplication ::applicationDirPath();
    QString mainwindow_bgm(":/music/tuanzi.wav");
    //set bgm
    music = new MusicLoader();
    music->loadMusic(mainwindow_bgm);


    //buttons
    single = new FullButton(":/button/start.png", "STORY", this);
    single->move(120, 500);

    choose = new FullButton(":/button/start.png", "SELECT", this);
    choose->move(460, 500);
    connect(choose, &FullButton::clicked, this, &init_choosewindow);

    to_exit = new FullButton(":/button/exit.png", "EXIT", this);
    to_exit->move(800, 500);
    connect(to_exit, &FullButton::clicked, this, &QWidget::close);

    //ChooseWindow
    choosewindow = new ChooseWindow();
    choosewindow->setParent(this);
    choosewindow->hide();
    connect(choosewindow, &ChooseWindow::game_start, this, &game_started);

    //PauseWindow
    pausewindow = new PauseWindow();
    pausewindow->setParent(this);
    pausewindow->hide();
    connect(gamescene, &Game::isPaused, this, &pause_now);
    connect(pausewindow, &PauseWindow::Resumed, this, &game_resumed);
    connect(gamescene, &Game::isResumed, this, &game_resumed);
    connect(pausewindow, &PauseWindow::Restarted, this, &game_started);

    //SettleWindow
    settlewindow = new SettleWindow();
    settlewindow->setParent(this);
    settlewindow->hide();
    connect(gamescene, &Game::toSettlement, this, &init_settlewindow);
    connect(settlewindow, &SettleWindow::Restarted, this, &game_started);

    //back to main
    connect(choosewindow, &ChooseWindow::back, this, &choosewindow_to_main);
    connect(pausewindow, &PauseWindow::BacktoMain, this, &pausewindow_to_main);
    connect(settlewindow, &SettleWindow::BacktoMain, this, &settlewindow_to_main);

    //DialogWindow
    dialogwindow = new DialogWindow();
    dialogwindow->setParent(this);
    dialogwindow->hide();
    connect(single,&FullButton::clicked,this,&init_dialogwindow);
    connect(dialogwindow,&DialogWindow::BacktoGame,this,&dialogwindow_to_game);

}

MainWindow::~MainWindow()
{
    delete background_label;
    delete single;
    delete choose;
    delete to_exit;
    delete choosewindow;
    delete pausewindow;
    delete settlewindow;
    delete gamescene;
    delete view;
    delete blur;
    //music->turnDownMusic();
    delete music;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (gamescene)
        gamescene->keyPressEvent(event);
}

