#ifndef MusicLoader_H
#define MusicLoader_H
#include <QtMultimedia>
#include<QMediaPlayer>
#include<QSoundEffect>
#include <QString>

class MusicLoader
{
public:
    MusicLoader();
    void loadMusic(QString music_filename);//加载音乐
    void changeMusic(QString music_filename); //切歌
    void turnDownMusic();    //关闭音乐
    void setSound(int x);  //设置音量
    float curVolume();//当前音量
    bool isPlaying();
    static int sound;   //统一声音大小


private:
    QSoundEffect *startsound;


};

#endif // MusicLoader_H
