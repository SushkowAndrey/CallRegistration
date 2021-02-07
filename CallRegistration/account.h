#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QMainWindow>
#include <QMessageBox>

#include "accountmodel.h"
#include "dbconnect.h"


namespace Ui {
class Account;
}

class Account : public QMainWindow
{
    Q_OBJECT

public:
    explicit Account(QWidget *parent = nullptr, int id=0);
    ~Account();

private slots:
    void on_pushButton_exit_clicked();

private:
    Ui::Account *ui;
    //ID аккаунта, который ввел корректный логин и пароль для передачи в данное окно
    int idAccount;
    //заполнение аккаунта первоначальными данными
    void AccountValue();
    //класс для передачи данных регистрируемого аккаунта для внесения в БД
    AccountModel accountModel;
    //колонки таблицы обращений
    void TableColumns();
};

#endif // ACCOUNT_H
