#include "loginwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
}


LoginWindow::~LoginWindow()
{
    delete ui;
    if(tradeWindow != nullptr)
        delete tradeWindow;
}


void LoginWindow::on_btn_login_clicked()
{
    QString user = ui->lineEdit_username->text();
    if(Database::userIsExist(user))
    {
        tradeWindow = new TradeWindow();
        connect(this, &LoginWindow::sendData, tradeWindow, &TradeWindow::recieveUserName);
        tradeWindow->show();
        emit sendData(user);
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
    if(ui->lineEdit_username->text().isEmpty())
    {
        QMessageBox message;
        message.setText("Введіть ім'я користувача!");
        message.exec();
        return;
    }
    QString user = ui->lineEdit_username->text();
    if(Database::userIsExist(user))
    {
        QMessageBox message;
        message.setText("Користувач з таким ім'ям вже існує!");
        message.exec();
    }
    else // якщо не існує
    {
        QMessageBox message;
        if(Database::accountIsCreated(user))
        {
            Database::createEmptyFieldsPortfolio(user);
            message.setText("Створено нового користувача: " + user);
            message.exec();
        }
        else
        {
            message.setText("Щось пішло не так!");
            message.exec();
        }
    }
}

