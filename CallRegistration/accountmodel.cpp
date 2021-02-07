#include "accountmodel.h"

AccountModel::AccountModel(){}

AccountModel::AccountModel(int id)
{
    this->id=id;
}

AccountModel::AccountModel(QString name, QString position, QString email, QString password, QString typeUser, QString departament)
{
    this->name=name;
    this->position=position;
    this->email=email;
    this->password=password;
    this->typeUser=typeUser;
    this->departament=departament;
}

AccountModel::AccountModel(QString email, QString password)
{
    this->email=email;
    this->password=password;
}
