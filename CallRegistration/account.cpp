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

void Account::AccountValue()
{
    ui->label->setText(QString::number(idAccount));
}
