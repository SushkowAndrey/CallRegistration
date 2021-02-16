#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QMainWindow>
#include <QMessageBox>
#include <QCheckBox>
#include <QVector>
#include <QDateEdit>

#include "accountmodel.h"
#include "dbconnect.h"
#include "appealcitizensmodel.h"


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
    //выходи з аккаунта
    void on_pushButton_exit_clicked();
    //добавление обращений
    void on_pushButton_add_appeal_citizens_clicked();

    void on_search_textChanged(const QString &arg1);

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
    //заполнение таблицы
    void FillingTable();
    //вектор для хранения данных из таблицы
    QVector <AppealCitizensModel> appealCitizensModel;
    //тип обращения
    /*QComboBox *typeRequest = new QComboBox();
    //медицинская организация
    QComboBox *medicalOrganization = new QComboBox();
*/
};

#endif // ACCOUNT_H
