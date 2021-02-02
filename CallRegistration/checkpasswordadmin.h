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
    explicit CheckPasswordAdmin(QWidget *parent = nullptr, AccountModel accountModel=0);
    ~CheckPasswordAdmin();

private slots:
    void on_pushButton_cancel_clicked();

    void on_pushButton_check_clicked();

private:
    Ui::CheckPasswordAdmin *ui;
    //класс для передачи данных регистрируемого аккаунта для внесения в БД
    AccountModel accountModel;
};

#endif // CHECKPASSWORDADMIN_H
