#include "dbconnect.h"

DBConnect::DBConnect()
{
    //запрос из базы данных
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);
    db.open();
}
//вход в ЛК
AccountModel DBConnect::SelectAccountModel(QString login, QString password)
{
    int idAccount;
    QSqlQuery query;
    query.exec("SELECT id FROM table_users WHERE email='"+login+"' AND password='"+password+"' AND active=1");
    if (query.next()) {
        idAccount = query.value(0).toInt();
        AccountModel accountModel(idAccount);
        return accountModel;
    } else {
        AccountModel accountModel(0);
        return accountModel;
    }
    db.close();
}

//заполнение ЛК
AccountModel DBConnect::SelectAccountModel(int id)
{
    QString name;
    QString position;
    QString departament;
    QString email;
    QString password;
    QString repeatePassword;
    QString typeUser;
    QSqlQuery query;
    query.exec("SELECT name, position, email, password, type_user, departament FROM table_users WHERE id="+QString::number(id)+" AND active=1");
    if (query.next()) {
        name = query.value(0).toString();;

        return accountModel;
    } else {
        AccountModel accountModel(0);
        return accountModel;
    }
    db.close();
}
//регистрация пользователя
bool DBConnect::RegistrationUser (AccountModel accountModel)
{
    QSqlQuery query;
    if (query.exec("INSERT INTO table_users (name, position, email, password, type_user, departament) "
                   "VALUES ('"+accountModel.name+"', '"+accountModel.position+"', '"+accountModel.email+"', '"+accountModel.password+"', '"+accountModel.typeUser+"', '"+accountModel.departament+"')"))
    {
        return true;
    } else {
        return false;
    }
    db.close();
}

//проверка пароля администратора
bool DBConnect::CheckPasswordAdmin (QString password)
{
    QSqlQuery query;
    if (query.exec("SELECT id FROM table_users WHERE password='"+password+"' AND active=1 AND type_user='1'"))
    {
        return true;
    } else {
        return false;
    }
    //db.close();
}

//проверка имеется ли данный пользователь в БД
bool DBConnect::CheckUser(QString name, QString position, QString email, QString departament)
{
    QSqlQuery query;
    if (query.exec("SELECT id FROM table_users WHERE name='"+name+"' AND position='"+position+"' AND email='"+email+"' AND departament='"+departament+"' AND active=1"))
    {
        return true;
    } else {
        return false;
    }
    db.close();
}
