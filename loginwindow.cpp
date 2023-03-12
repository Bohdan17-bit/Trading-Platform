#include "loginwindow.h"
#include "ui_loginwindow.h"


LoginWindow::LoginWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    setWindowTitle("Вхід");
    user = new User();
    sound = new Sound();
}


LoginWindow::~LoginWindow()
{
    delete ui;
    if(tradeWindow != nullptr)
        delete tradeWindow;
}


void LoginWindow::showDialogLoading()
{
    QMovie *movie_loading = new QMovie("./images/loading.gif");
    movie_loading->setScaledSize(QSize(75, 75));

    loading_window = new QWidget();
    loading_window->setFixedSize(75, 75);

    QLabel *label_process = new QLabel(loading_window);
    label_process->setMovie(movie_loading);
    movie_loading->start();

    loading_window->setAttribute(Qt::WA_TranslucentBackground );
    loading_window->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    loading_window->setWindowTitle("Завантаження...");

    loading_window->show();
}


void LoginWindow::on_btn_login_clicked()
{
    QString user_name = ui->lineEdit_username->text();

    if(user->userIsExists(user_name))
    {
        sound->transitionOnAnotherWindow();

        user->setUsername(user_name);
        user->loadUserData();
        showDialogLoading();

        tradeWindow = new TradeWindow(user);

        connect(this, &LoginWindow::sendSoundObj, tradeWindow, &TradeWindow::getSoundObj);
        emit sendSoundObj(sound);
        tradeWindow->show();

        this->close();
        loading_window->close();
    }

    else
    {
        QMessageBox message;
        message.setText("Не знайдено користувача з таким ім'ям!");
        sound->error();
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
        sound->error();
        message.exec();
        return;
    }

    if(user->userIsExists(user_name))
    {
        QMessageBox message;
        message.setText("Користувач з таким ім'ям вже існує!");
        sound->error();
        message.exec();
    }
    else // якщо не існує
    {
        QMessageBox message;
        if(user->createNewUser(user_name))
        {
            message.setText("Створено нового користувача: " + user_name);
            sound->processComplete();
            message.exec();
        }
        else
        {
            message.setText("Щось пішло не так!");
            sound->error();
            message.exec();
        }
    }
}

