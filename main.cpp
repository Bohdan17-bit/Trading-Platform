#include "window/loginwindow.h"
#include <QApplication>
#include <utils/sound.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("./images/icon.png"));
    Sound *sound = new Sound();
    LoginWindow loginWindow(sound);
    loginWindow.show();
    return a.exec();
}
