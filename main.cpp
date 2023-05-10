#include "window/loginwindow.h"
#include <QApplication>
#include <utils/sound.h>
#include <QSettings>
#include <QTranslator>
#include <QLocale>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("./images/icon.png"));

    QTranslator *translator = new QTranslator();

    QSettings *settings = new QSettings("preferences.ini",QSettings::IniFormat);
    QString locale = settings->value("settings/language", "en").toString();

    translator->load(QApplication::applicationName() + "_" + locale);
    a.installTranslator(translator);

    Sound *sound = new Sound();
    LoginWindow loginWindow(sound, translator);
    loginWindow.show();
    return a.exec();
}
