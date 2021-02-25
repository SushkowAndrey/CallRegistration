#ifndef DBCONNECT_H
#define DBCONNECT_H

#include <QString>
#include <QVector>

#include "QtSql"
#include "QSqlDatabase"
#include "QSqlQuery"
#include "accountmodel.h"
#include "log.h"
#include "appealcitizensmodel.h"
#include "categorucitizens.h"

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
    //смена пароля пользователя
    bool ChangePasswordUser (AccountModel accountModel);
    //заполнение таблицы с обращениям
    QVector <AppealCitizensModel> TableAppealCitizens();
    //количество строк в таблице
    int CountOrganization();
    //запись в БД
    bool AddAppealCitizens(AppealCitizensModel appealCitizensModel);
    //справочники
    //справочник категорий граждан
    QStringList CategoryCitizens();
    //справочник медицинских организаций
    QStringList MedicalOrganization();
    //типы обращений
    QStringList TypeRequestId();
    //перечень пользователей
    QStringList TableUsersId();
    //редактирование данных
    void EditingApplicant(QString data, int row, int column);



private:
    //путь БД и экземпляр БД
    const QString path="Database.sqlite";
    QSqlDatabase db;
};

#endif // DBCONNECT_H
