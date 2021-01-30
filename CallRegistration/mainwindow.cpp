#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "account.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{ 
    ui->setupUi(this);
    Log::SaveLog("Запуск программы", this);    //запись лога
    //по умолчанию первый индекс (c полем логина и пароля)
    ui->stackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_close_clicked()
{
    this->close();
}

void MainWindow::on_pushButton_clear_clicked()
{
    ui->input_login->clear();
    ui->input_login->clear();
}

void MainWindow::on_pushButton_recover_clicked()
{
    //переход на другое окно для восстановления активности пользователя
    ui->stackedWidget->setCurrentIndex(1);
    Log::SaveLog("Восстановление пользователя или пароля", this);    //запись лога
}

void MainWindow::on_pushButton_back_clicked()
{
    //переход на поле с логином и паролем назад
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_authorization_clicked()
{
    QString login=ui->input_login->text();
    QString password=ui->input_password->text();
    if (login.size()==0||password.size()==0)
    {
        ui->invalid_data->setText("Введите логин и/или пароль");
    } else {
    Log::SaveLog("Попытка аутентификации пользователя с логином", login, this);    //запись лога
    //модель базы данных
    DBConnect dbConnect;
    AccountModel accountModel=dbConnect.SelectAccountModel(login, password);
    if (accountModel.id>0) {
    //открытие личного кабинета пользователя
    account = new Account (this, accountModel.id);
    this->close();
    account->show();
    Log::SaveLog("Вход в личный кабинет пользователя с логином "+login, this);    //запись лога
    } else {
        ui->invalid_data->setText("Неверные идентификационные данные или пользователь неактивен");
        Log::SaveLog("Неверные идентификационные данные или пользователь неактивен", this);    //запись лога
    }
    }

}
