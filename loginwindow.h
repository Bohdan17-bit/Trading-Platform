#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include "tradewindow.h"
#include "user.h"
#include <QMessageBox>
#include "sound.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();
    void showDialogLoading();

signals:
    void sendSoundObj(Sound *sound);

private slots:
    void on_btn_new_account_clicked();
    void on_btn_login_clicked();

private:
    Ui::LoginWindow *ui;
    TradeWindow *tradeWindow;
    User *user;
    Sound *sound;
    QWidget *loading_window;
};

#endif // LOGINWINDOW_H
