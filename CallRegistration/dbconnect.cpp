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
    QString email;
    QString password;
    QString typeUser;
    QString departament;
    QSqlQuery query;
    query.exec("SELECT name, position, email, password, type_user, departament FROM table_users WHERE id="+QString::number(id)+" AND active=1");
    if (query.next()) {
        name = query.value(0).toString();
        position = query.value(1).toString();
        email = query.value(2).toString();
        password = query.value(3).toString();
        typeUser = query.value(4).toString();
        departament = query.value(5).toString();
        AccountModel accountModel(name, position, email, password, typeUser, departament);
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

bool DBConnect::BlockUser(QString email)
{
    QSqlQuery query;
    if (query.exec("UPDATE table_users SET active = 0 WHERE email='"+email+"' AND type_user='2'"))
    {
        return true;
    } else {
        return false;
    }
    db.close();
}

bool DBConnect::ActiveUser (QString email)
{
    QSqlQuery query;
    if (query.exec("UPDATE table_users SET active = 1 WHERE email='"+email+"' AND type_user='2'"))
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
    query.exec("SELECT id FROM table_users WHERE password='"+password+"' AND active=1 AND type_user='1'");
    if (query.first())
    {
        return true;
    } else {
        return false;
    }
    //db.close();
}

//проверка имеется ли данный пользователь в БД
bool DBConnect::CheckUser(QString email)
{
    QSqlQuery query;
    query.exec("SELECT id FROM table_users WHERE email='"+email+"'");
    if (query.first())
    {
        return true;
    } else {
        return false;
    }
    db.close();
}

//проверка активности
bool DBConnect::CheckActive(QString email)
{
    QString active;
    QSqlQuery query;
    query.exec("SELECT active FROM table_users WHERE email='"+email+"'");
    if (query.first()) {
        active = query.value(0).toString();
        if (active=="1") return true;
        else if (active=="0") return false;
    } else return false;
    db.close();
}

//смена пароля пользователя
bool DBConnect::ChangePasswordUser(AccountModel accountModel)
{
    QSqlQuery query;
    if (query.exec("UPDATE table_users SET password = '"+accountModel.password+"' WHERE email='"+accountModel.email+"'"))
    {
        return true;
    } else {
        return false;
    }
    db.close();
}

//заполнение таблицы с обращениям
QVector <AppealCitizensModel> DBConnect::TableAppealCitizens()
{
    QVector <AppealCitizensModel> Temp;
    QSqlQuery query;
    query.exec("SELECT id,applicant, category_citizens_id, year_birth,contact, "
               "medical_organization_id, type_request_id, description, date_request, "
               "transmitted, result,table_users_id, sign_closure, anonymous_appeal, closing_date, comments FROM appeal_citizens");
    while(query.next())
    {
        AppealCitizensModel appealCitizensModel(query.value(0).toString(), query.value(1).toString(), query.value(2).toString(), query.value(3).toString(), query.value(4).toString(),
                                                query.value(5).toString(), query.value(6).toString(), query.value(7).toString(), query.value(8).toString(),
                                                query.value(9).toString(), query.value(10).toString(), query.value(11).toString(), query.value(12).toString(),
                                                query.value(13).toString(), query.value(14).toString(), query.value(15).toString());
        Temp.push_back(appealCitizensModel);
    }
    db.close();
    return Temp;
}
