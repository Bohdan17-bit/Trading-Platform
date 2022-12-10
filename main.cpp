#include "loginwindow.h"
#include <QApplication>
#include "database.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Database::initDatabase();
    Database::openDatabase();
    LoginWindow loginWindow;
    loginWindow.show();
    return a.exec();
}
