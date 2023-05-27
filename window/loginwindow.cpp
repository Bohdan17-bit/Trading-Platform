#include "window/loginwindow.h"
#include "ui_loginwindow.h"
#include "storage/database.h"


LoginWindow::LoginWindow(Sound *sound, QTranslator *translator, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("Вхід"));
    user = new User();
    this->sound = sound;
    this->translator = translator;
    Database::openDatabase();
}


LoginWindow::~LoginWindow()
{
    delete loading_window;
    delete ui;
}


void LoginWindow::closeEvent(QCloseEvent *event)
{
    Database::closeDatabase();
}


void LoginWindow::showDialogLoading()
{
    QMovie *movie_loading = new QMovie(this);
    movie_loading->setFileName("./images/loading.gif");
    movie_loading->setScaledSize(QSize(75, 75));

    loading_window = new QWidget();
    int sizeWindowLoading = 75;
    loading_window->setFixedSize(sizeWindowLoading, sizeWindowLoading);

    QLabel *label_process = new QLabel(loading_window);
    label_process->setMovie(movie_loading);
    movie_loading->start();

    loading_window->setAttribute(Qt::WA_TranslucentBackground );
    loading_window->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    loading_window->setWindowTitle(tr("Завантаження..."));

    int parentWidth = this->width();
    int parentHeight = this->height();

    int childWidth = sizeWindowLoading;
    int childHeight = sizeWindowLoading;

    int x = this->geometry().x() + (parentWidth - childWidth) / 2;
    int y = this->geometry().y() + (parentHeight - childHeight) / 2;

    loading_window->move(x, y);
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

        tradeWindow = new TradeWindow(user, translator);

        connect(this, &LoginWindow::sendSoundObj, tradeWindow, &TradeWindow::getSoundObj);
        emit sendSoundObj(sound);

        this->close();
        loading_window->close();
        tradeWindow->show();

    }

    else
    {
        QMessageBox message;
        message.setText(tr("Не знайдено користувача з таким ім'ям!"));
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
        message.setText(tr("Введіть ім'я користувача!"));
        sound->error();
        message.exec();
        return;
    }

    if(user->userIsExists(user_name))
    {
        QMessageBox message;
        message.setText(tr("Користувач з таким ім'ям вже існує!"));
        sound->error();
        message.exec();
    }
    else
    {
        QMessageBox message;
        if(user->createNewUser(user_name))
        {
            message.setText(tr("Створено нового користувача: ") + user_name);
            sound->processComplete();
            message.exec();
        }
        else
        {
            message.setText(tr("Щось пішло не так!"));
            sound->error();
            message.exec();
        }
    }
}

