#include "dbconnect.h"

DBConnect::DBConnect()
{
    //запрос из базы данных
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);
    db.open();
}

AccountModel DBConnect::SelectAccountModel(QString login, QString password)
{
    int idAccount;
    QSqlQuery query;
    query.exec("SELECT id FROM table_users WHERE email='"+login+"' AND password='"+password+"' AND active=1");
    if (query.next()) {
        Log::SaveLog("AccountModel accountModel(idAccount)");    //запись лога
        idAccount = query.value(0).toInt();
        AccountModel accountModel(idAccount);
        return accountModel;
    } else {
        Log::SaveLog("AccountModel accountModel(0)");    //запись лога
        AccountModel accountModel(0);
        return accountModel;
    }
    db.close();
}
