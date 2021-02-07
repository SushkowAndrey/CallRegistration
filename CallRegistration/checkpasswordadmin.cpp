#include "checkpasswordadmin.h"
#include "ui_checkpasswordadmin.h"

CheckPasswordAdmin::CheckPasswordAdmin(QWidget *parent, AccountModel accountModel, bool temp) :
    QDialog(parent),
    ui(new Ui::CheckPasswordAdmin)
{
    ui->setupUi(this);
    this->accountModel=accountModel;
    connect (ui->pushButton_check, SIGNAL (clicked()), this, SLOT(Registration()));
}

CheckPasswordAdmin::CheckPasswordAdmin(QWidget *parent, QString email, bool temp) :
    QDialog(parent),
    ui(new Ui::CheckPasswordAdmin)
{
    ui->setupUi(this);
    this->email=email;
    connect (ui->pushButton_check, SIGNAL (clicked()), this, SLOT(Block()));
}

CheckPasswordAdmin::CheckPasswordAdmin(QWidget *parent, QString email, int temp) :
    QDialog(parent),
    ui(new Ui::CheckPasswordAdmin)
{
    ui->setupUi(this);
    this->email=email;
    this->isActive=isActive;
    connect (ui->pushButton_check, SIGNAL (clicked()), this, SLOT(Activate()));
}

CheckPasswordAdmin::CheckPasswordAdmin(QWidget *parent, AccountModel accountModel, int temp) :
    QDialog(parent),
    ui(new Ui::CheckPasswordAdmin)
{
    ui->setupUi(this);
    this->accountModel=accountModel;
    connect (ui->pushButton_check, SIGNAL (clicked()), this, SLOT(ChangingPassword()));
}


CheckPasswordAdmin::~CheckPasswordAdmin()
{
    delete ui;
}

//отмена регистрации после ввода информации
void CheckPasswordAdmin::on_pushButton_cancel_clicked()
{
    this->close();
}

void CheckPasswordAdmin::Registration()
{
    QString password=ui->enter_password->text();
    if (password.size()==0) {
        QMessageBox::critical(this, "Ошибка","Введите пароль администратора");
    } else {
    DBConnect dbConnect;
    if (dbConnect.CheckPasswordAdmin(password)) {
    if (dbConnect.RegistrationUser(accountModel))
    {
        QMessageBox::information(this, "Результат","Успешная регистрация пользователя " + accountModel.email);
        Log::SaveLog("Пользователь с email", accountModel.email, "- зарегистрирован", this);    //запись лога
        this->close();
    }
    else {
        QMessageBox::critical(this, "Результат","Пользователь не зарегистрирован");
    }
    } else {
        QMessageBox::critical(this, "Результат","Неверный пароль администратора");
        Log::SaveLog("Попытка проведения операции регистрации пользователя не администратором", this);    //запись лога
    }
    }
}

void CheckPasswordAdmin::Block()
{
    QString password=ui->enter_password->text();
    if (password.size()==0) {
        QMessageBox::critical(this, "Ошибка","Введите пароль администратора");
    } else {
    DBConnect dbConnect;
    if (dbConnect.CheckPasswordAdmin(password)) {
    if (dbConnect.BlockUser(email))
    {
        QMessageBox::information(this, "Результат","Успешная блокировка пользователя " + email);
        Log::SaveLog("Пользователь с email", email, " - заблокирован", this);    //запись лога
        this->close();
    }
    else {
        QMessageBox::critical(this, "Результат","Пользователь не заблокирован");
    }
    } else {
        QMessageBox::critical(this, "Результат","Неверный пароль администратора");
        Log::SaveLog("Попытка проведения операции блокирования пользователя не администратором", this);    //запись лога
    }
    }
}

void CheckPasswordAdmin::Activate()
{
    QString password=ui->enter_password->text();
    if (password.size()==0) {
        QMessageBox::critical(this, "Ошибка","Введите пароль администратора");
    } else {
    DBConnect dbConnect;
    if (dbConnect.CheckPasswordAdmin(password)) {
    if (dbConnect.ActiveUser(email))
    {
        QMessageBox::information(this, "Результат","Успешная активация пользователя " + email);
        Log::SaveLog("Пользователь с email", email, " - активирован", this);    //запись лога
        this->close();
    }
    else {
        QMessageBox::critical(this, "Результат","Пользователь не заблокирован");
    }
    } else {
        QMessageBox::critical(this, "Результат","Неверный пароль администратора");
        Log::SaveLog("Попытка проведения операции активации пользователя не администратором", this);    //запись лога
    }
    }
}

void CheckPasswordAdmin::ChangingPassword()
{
    Log::SaveLog("лог 2", this);    //запись лога
    QString password=ui->enter_password->text();
    if (password.size()==0) {
        QMessageBox::critical(this, "Ошибка","Введите пароль администратора");
    } else {
    DBConnect dbConnect;
    if (dbConnect.CheckPasswordAdmin(password)) {
    if (dbConnect.ChangePasswordUser(accountModel))
    {
        QMessageBox::information(this, "Результат","Успешная смена пароля пользователя " + email);
        Log::SaveLog("Изменен пароля пользователя с email", accountModel.email, this);    //запись лога
        this->close();
    }
    else {
        QMessageBox::critical(this, "Результат","Пароль не сменен");
    }
    } else {
        QMessageBox::critical(this, "Результат","Неверный пароль администратора");
        Log::SaveLog("Попытка проведения операции смены пароля пользователя не администратором", this);    //запись лога
    }
    }


}
