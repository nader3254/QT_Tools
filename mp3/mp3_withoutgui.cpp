#include "mp3_withoutgui.h"

mp3_WithoutGUI::mp3_WithoutGUI()
{
    _mp3 = new QMediaPlayer(this);
   // _mp3->setMedia(QUrl::fromLocalFile("./Tones/tone1.mp3"));
    connect(_mp3, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));


}

void mp3_WithoutGUI::Play(QString path, int volumeLevel)
{
    //_mp3->setMedia(QUrl::fromLocalFile("./Tones/tone10.mp3"));
    _mp3->setMedia(QUrl::fromLocalFile(path));
    _mp3->setVolume(volumeLevel);
    _mp3->play();
    qDebug()<<_mp3->errorString();
}

void mp3_WithoutGUI::Play(QString path)
{
    _mp3->setMedia(QUrl::fromLocalFile(path));
    _mp3->play();
    qDebug()<<_mp3->errorString();
}

void mp3_WithoutGUI::Pause()
{
    _mp3->pause();
    qDebug()<<_mp3->errorString();
}
void mp3_WithoutGUI::positionChanged(qint64 x)
{

}
