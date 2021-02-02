#include "checkpasswordadmin.h"
#include "ui_checkpasswordadmin.h"

CheckPasswordAdmin::CheckPasswordAdmin(QWidget *parent, AccountModel accountModel) :
    QDialog(parent),
    ui(new Ui::CheckPasswordAdmin)
{
    ui->setupUi(this);
    this->accountModel=accountModel;
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


void CheckPasswordAdmin::on_pushButton_check_clicked()
{
    QString password=ui->enter_password->text();
    if (password.size()==0) {
        QMessageBox::critical(this, "Ошибка","Введите пароль администратора");
    } else {
    DBConnect dbConnect;
    if (dbConnect.CheckPasswordAdmin(password)) {
    if (dbConnect.RegistrationUser(accountModel))
    {
        QMessageBox::information(this, "Результат","Успешная регистрация пользователя ");
        Log::SaveLog("Пользователь с логином - зарегистрирован", this);    //запись лога
    }
    else {
        QMessageBox::critical(this, "Результат","Пользователь не зарегистрирован");
    }
    } else {
        QMessageBox::critical(this, "Результат","неверный пароль администратора");
    }
    }
}
