#ifndef MP3_WITHOUTGUI_H
#define MP3_WITHOUTGUI_H

#include <QDebug>
#include <QWidget>
#include <QMediaPlayer>

class mp3_WithoutGUI : public QObject
{
    Q_OBJECT
public:
    mp3_WithoutGUI();
    void Play(QString path,int volumeLevel);
    void Play(QString path);
    void Pause();

public slots:
   void positionChanged(qint64 x);


private:
    QMediaPlayer *_mp3;

};

#endif // MP3_WITHOUTGUI_H
