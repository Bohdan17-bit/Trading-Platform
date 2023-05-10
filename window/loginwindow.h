#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include "window/tradewindow.h"
#include "visitor/user.h"
#include <QMessageBox>
#include "utils/sound.h"
#include <QTranslator>
namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(Sound *sound, QTranslator *translator, QWidget *parent = nullptr);
    ~LoginWindow();
    void showDialogLoading();

signals:
    void sendSoundObj(Sound *sound);

private slots:
    void closeEvent(QCloseEvent *event) override;
    void on_btn_new_account_clicked();
    void on_btn_login_clicked();

private:
    Ui::LoginWindow *ui;
    TradeWindow *tradeWindow;
    User *user;
    Sound *sound;
    QTranslator *translator;
    QWidget *loading_window;
};

#endif // LOGINWINDOW_H
