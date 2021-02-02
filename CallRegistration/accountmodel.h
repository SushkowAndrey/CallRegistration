#ifndef ACCOUNTMODEL_H
#define ACCOUNTMODEL_H

#include <QString>

//модель аккаунта оператора
class AccountModel
{
public:
    int id;
    QString name;
    QString position;
    QString email;
    QString password;
    QString departament;
    QString typeUser;
    bool active;

    AccountModel();
    //конструктор для передачи информации о ID пользователя в окно работы с обращениями
    AccountModel(int id);
    //конструктор для пользователя
    AccountModel(QString name, QString position, QString email, QString password, QString typeUser, QString departament);
};

#endif // ACCOUNTMODEL_H
