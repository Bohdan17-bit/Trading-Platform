#include "sound.h"
#include "QUrl"

Sound::Sound()
{
    path = "./sound/";
    soundEffect = new QSoundEffect();
    soundEffect->setVolume(0.2f);
}

void Sound::transitionOnAnotherWindow()
{
    soundEffect->setSource(QUrl::fromLocalFile(path + "joystick_trigger.wav"));
    soundEffect->play();
}

void Sound::error()
{
    soundEffect->setSource(QUrl::fromLocalFile(path + "click-error.wav"));
    soundEffect->play();
}

void Sound::hover()
{
    soundEffect->setSource(QUrl::fromLocalFile(path + "interface-hover.wav"));
    soundEffect->play();
}

void Sound::simpleClick()
{
    soundEffect->setSource(QUrl::fromLocalFile(path + "interface_click.wav"));
    soundEffect->play();
}

void Sound::processComplete()
{
    soundEffect->setSource(QUrl::fromLocalFile(path + "process_complete.wav"));
    soundEffect->play();
}

void Sound::close()
{
    soundEffect->setSource(QUrl::fromLocalFile(path + "closing_effect.wav"));
    soundEffect->play();
}
