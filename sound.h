#ifndef SOUND_H
#define SOUND_H
#include <QtMultimedia/QSoundEffect>

class Sound
{
public:
    Sound();
    void transitionOnAnotherWindow();
    void error();
    void hover();
    void simpleClick();
    void processComplete();
    void close();
private:
    QSoundEffect *soundEffect;
    QString path;
};

#endif // SOUND_H
