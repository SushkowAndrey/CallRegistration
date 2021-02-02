#include "account.h"
#include "ui_account.h"

Account::Account(QWidget *parent, int idAccount) :
    QMainWindow(parent),
    ui(new Ui::Account)
{
    ui->setupUi(this);
    this->idAccount=idAccount;
    AccountValue();
}

Account::~Account()
{
    delete ui;
}

//заполнение аккаунта
void Account::AccountValue()
{
    DBConnect dbConnect;


    ui->label->setText(QString::number(idAccount));
}



//выход из формы
void Account::on_pushButton_exit_clicked()
{
    this->close();
}
