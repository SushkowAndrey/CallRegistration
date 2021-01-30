#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QMainWindow>

namespace Ui {
class Account;
}

class Account : public QMainWindow
{
    Q_OBJECT

public:
    explicit Account(QWidget *parent = nullptr, int id=0);
    ~Account();

private:
    Ui::Account *ui;
    //ID аккаунта, который ввел корректный логин и пароль для передачи в данное окно
    int idAccount;
    //заполнение аккаунта первоначальными данными
    void AccountValue();
};

#endif // ACCOUNT_H
