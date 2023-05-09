#include "window/loginwindow.h"
#include <QApplication>
#include <utils/sound.h>
#include <QSettings>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("./images/icon.png"));
    //QSettings *settings = new QSettings("preferences.ini", QSettings::IniFormat);
    //settings->setValue("settings/language", "ua");
    //settings->sync();
    QSettings *settings2 = new QSettings("preferences.ini",QSettings::IniFormat);
      qDebug() << settings2->value("settings/language", "en").toString();
    Sound *sound = new Sound();
    LoginWindow loginWindow(sound);
    loginWindow.show();
    return a.exec();
}
