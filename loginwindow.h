#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include "tradewindow.h"
#include "user.h"
#include <QMessageBox>


namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void on_btn_login_clicked();
    void on_btn_new_account_clicked();

private:
    Ui::LoginWindow *ui;
    TradeWindow *tradeWindow;
    User *user;
};

#endif // LOGINWINDOW_H
