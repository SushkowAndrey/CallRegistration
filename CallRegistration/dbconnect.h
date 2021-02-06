#ifndef DBCONNECT_H
#define DBCONNECT_H

#include <QString>

#include "QtSql"
#include "QSqlDatabase"
#include "QSqlQuery"
#include "accountmodel.h"
#include "log.h"

class DBConnect
{
public:
    DBConnect();
    //проверка наличия пользователя в ЛК в БД
    AccountModel SelectAccountModel(QString login, QString password);
    //информация о пользователе по ID
    AccountModel SelectAccountModel(int id);
    //регистрация пользователя
    bool RegistrationUser (AccountModel accountModel);
    //блокировка пользователя
    bool BlockUser (QString email);
    //активация пользователя
    bool ActiveUser (QString email);
    //проверка пароля администратора
    bool CheckPasswordAdmin (QString password);
    //проверка наличия пользователя в базе
    bool CheckUser (QString email);
    //проверка активности пользователя
    bool CheckActive (QString email);

private:
    //путь БД и экземпляр БД
    const QString path="Database.sqlite";
    QSqlDatabase db;
};

#endif // DBCONNECT_H
