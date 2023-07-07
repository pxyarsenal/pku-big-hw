#ifndef TXTSHOW_H
#define TXTSHOW_H
#include<QApplication>
#include<QLabel>
#include<QWidget>
#include<QObject>
#include<QTimer>
#include<QString>
#include<QFont>
#include<QThread>
#include<QTime>

//用于逐个输出文字
//设置字体字号
//后期可考虑加入日语

class TxtShow:public QObject
{

private:
    QString str;
    QLabel *lab;
    QFont font;
    const QString words_style_options[6]={"Microsoft YaHei","KaTi","FangSong"};  //可选字体
    const int words_size_options[6]={10,20,30,40,5,16};//可选字号
    int inc;
    int idx;
    int inter;
    int word_size;          //0,1,2,3,4,5
    int word_style;         //0,1,2,3,4,5

public:
    TxtShow()
        :inc(0),word_size(20),word_style(0),inter(100)
    {
    };

    void load(QString st,QLabel *lb);
    void setSpeed(int speed); //设置打字速度
    void reset();
    QString Str();
    QString LabStr();
    void timChanged();
    void setSize(int x);
    void setStyle(int index);
    //void keyPressEvent(QKeyEvent* event);
    void mousePressEvent(QMouseEvent *ev);

};


#endif // TXTSHOW_H
