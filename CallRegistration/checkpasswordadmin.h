#ifndef CHECKPASSWORDADMIN_H
#define CHECKPASSWORDADMIN_H

#include <QDialog>

#include "accountmodel.h"
#include "dbconnect.h"

//класс для проверки пароля при проведении операций администратором
namespace Ui {
class CheckPasswordAdmin;
}

class CheckPasswordAdmin : public QDialog
{
    Q_OBJECT

public:
    explicit CheckPasswordAdmin(QWidget *parent = nullptr, AccountModel accountModel=0);//при регистрации пользователя
    explicit CheckPasswordAdmin(QWidget *parent = nullptr, QString mail=0);//при блокировке пользователя
    ~CheckPasswordAdmin();

private slots:
    //отмена изменений
    void on_pushButton_cancel_clicked();
    //слоты регистрации пользователя
    void Registration();
    void Block();

private:
    Ui::CheckPasswordAdmin *ui;
    //класс для передачи данных регистрируемого аккаунта для внесения в БД
    AccountModel accountModel;
    //почта, которая передается в конструктор при блокировке
    QString email;
};

#endif // CHECKPASSWORDADMIN_H
