#include "dialogwindow.h"
#include "config.h"
#include <QDebug>
#include <QFile>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QThread>

TxtShow txt;


DialogWindow::DialogWindow(QWidget* parent)
    :QWidget{parent}
{
    order = 1;
    background_label = new QLabel(this);
    setFixedSize(WIDTH, HEIGHT);
    QPixmap background(":/background/dialog.png");
    background_label->setPixmap(background.scaled(size()));
    background_label->setAlignment(Qt::AlignBottom);
}

void DialogWindow::startDialog(){
    QLabel *outputter = new QLabel;
    outputter->setParent(this);
    QImage *img=new QImage;

    outputter->resize(900,500);
    outputter->move(100,350);
    outputter ->show();
    char tem1= order+'0';
    QString txtaddress = ":/text/dialog";
    txtaddress.append(tem1);
    txtaddress.append(".txt");
    outputter->show();




    QFile file(txtaddress);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {

        while (!file.atEnd())
        {


            QByteArray line = file.readLine();
            QString str(line);
            txt.load(str,outputter);
            txt.setSize(20);
            txt.setSpeed(300);
            txt.setStyle(0);
            txt.timChanged();
            outputter ->show();
            QThread::msleep(500);//每次鼠标点击之后在这个地方停两秒
        }
        outputter->hide();
        QString str("");
        txt.load(str,outputter);

        file.close();
    }

}


void DialogWindow::BacktoGame(){

}



//void DialogWindow::keyPressEvent(QKeyEvent* event){

//    if(event->key() == Qt::Key_Escape){
//        po = (po+1)%2;
//        txt.setSpeed(speed[po]);
//    }
//}

int speeds[2] ={1,100};
int posi = 1;

void DialogWindow::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button() == Qt::LeftButton){

        posi = (posi+1)%2;
        txt.setSpeed(speeds[posi]);
        qDebug()<<1;
    }
}
