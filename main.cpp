#include "window/loginwindow.h"
#include <QApplication>
#include "storage/database.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("./images/icon.png"));
    LoginWindow loginWindow;
    loginWindow.show();
    return a.exec();
}
