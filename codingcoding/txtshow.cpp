#include "txtshow.h"
#include<QKeyEvent>
#include<QMouseEvent>
#include<QDebug>

void TxtShow::load(QString st, QLabel *lb)
{
    str=st;
    lab=lb;
    lab->setWordWrap(true);
}

void TxtShow::setSpeed(int speed)
{
    inter=speed;
}

void TxtShow::reset()
{
    inc=0;
}

QString TxtShow::Str()
{
    return str;
}

QString TxtShow::LabStr()
{
    return lab->text();
}

void TxtShow::timChanged()
{
    setSize(word_size);
    setStyle(word_style);
    lab->setFont(font);

    while(inc<str.size()){
        if(inc>=str.size()){
            break;
        }
        else
        {
            lab->setText(str.left(inc));

            inc++ ;
            lab->show();
        }

        QEventLoop eventloop;
        qDebug()<<inter;
        QTimer::singleShot(inter, &eventloop, SLOT(quit()));
        eventloop.exec();
    }
    inc=0;
}

void TxtShow::setSize(int x){
    font.setPointSize(x);
}

void TxtShow::setStyle(int index){
    font.setFamily(words_style_options[index]);
}

//int speed[2] ={10,100};
//int po = 1;

//void TxtShow::keyPressEvent(QKeyEvent* event){

//    if(event->key() == Qt::Key_Space){
//        po = (po+1)%2;
//        this->setSpeed(speed[po]);
//        qDebug()<<1;
//    }
//}
int speed[2] ={10,100};
int po = 1;

void TxtShow::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button() == Qt::LeftButton){

        po = (po+1)%2;
        this->setSpeed(speed[po]);
        qDebug()<<1;
    }
}
