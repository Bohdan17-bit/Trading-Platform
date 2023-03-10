#include "loginwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    setWindowTitle("Вхід");
    user = new User();
}


LoginWindow::~LoginWindow()
{
    delete ui;
    if(tradeWindow != nullptr)
        delete tradeWindow;
}


void LoginWindow::on_btn_login_clicked()
{
    QString user_name = ui->lineEdit_username->text();

    if(user->userIsExists(user_name))
    {
        user->setUsername(user_name);
        user->loadUserData();
        tradeWindow = new TradeWindow(user);
        tradeWindow->show();
        this->close();
    }

    else
    {
        QMessageBox message;
        message.setText("Не знайдено користувача з таким ім'ям!");
        message.exec();
    }
}


void LoginWindow::on_btn_new_account_clicked()
{
    QString user_name = ui->lineEdit_username->text();

    if(ui->lineEdit_username->text().isEmpty())
    {
        QMessageBox message;
        message.setText("Введіть ім'я користувача!");
        message.exec();
        return;
    }

    if(user->userIsExists(user_name))
    {
        QMessageBox message;
        message.setText("Користувач з таким ім'ям вже існує!");
        message.exec();
    }
    else // якщо не існує
    {
        QMessageBox message;
        if(user->createNewUser(user_name))
        {
            message.setText("Створено нового користувача: " + user_name);
            message.exec();
        }
        else
        {
            message.setText("Щось пішло не так!");
            message.exec();
        }
    }
}

