#include "musicloader.h"

int MusicLoader::sound =100;

MusicLoader::MusicLoader()
{

    startsound = new QSoundEffect(nullptr);
    startsound->setVolume(sound);
}

void MusicLoader::loadMusic(QString music_filename){

    startsound->setSource(QUrl::fromLocalFile(music_filename));
    startsound->setVolume(100);
    startsound->setLoopCount(QSoundEffect::Infinite);//设置循环次数int；  QSoundEffect::Infinite 枚举值 无限循环
    startsound->play();//软件启动自动播放

}

void MusicLoader::changeMusic(QString music_filename){
    startsound->stop();
    startsound->setSource(QUrl::fromLocalFile(music_filename));
    startsound->setLoopCount(QSoundEffect::Infinite);//设置循环次数int；  QSoundEffect::Infinite 枚举值 无限循环
    startsound->play();
}

void MusicLoader::turnDownMusic(){
    startsound->stop();
}

void MusicLoader::setSound(int x){
    startsound->setVolume(x);
    sound = x;
}

bool MusicLoader::isPlaying(){
    return startsound->isPlaying();
}

float MusicLoader::curVolume(){
    return startsound->volume();
}
