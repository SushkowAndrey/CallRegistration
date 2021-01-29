#ifndef DBCONNECT_H
#define DBCONNECT_H

#include <QString>

#include "QtSql"
#include "QSqlDatabase"
#include "QSqlQuery"

class DBConnect
{
public:
    DBConnect();

private:
    //путь БД и экземпляр БД
    const QString path="D:\\Programing\\ExtractRecipes-2\\DataProject.sqlite";
    QSqlDatabase db;
};

#endif // DBCONNECT_H

