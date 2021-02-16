#ifndef APPEALCITIZENSMODEL_H
#define APPEALCITIZENSMODEL_H

#include <QString>
#include <QDate>

class AppealCitizensModel
{
public:
    int id;
    QString applicant; //ФИО заявителя
    int categoryCitizensId;//категория заявителя
    QString yearBirth;//год рождения
    QString contact;//адрес и телефон
    QString medicalOrganizationId;//медицинская организация
    QString typeRequestId;//тип обращения
    QString description; //описание
    QString dateRequest; //дата обращения
    QString transmitted; //кому передано
    QString result;//результат
    QString tableUsersId;//кто принял
    QString signClosure;//признак закрытия
    QString anonymousAppeal;//анонимное или нет
    QString closingDate;//дата закрытия
    QString comments;//комментарий
public:
    AppealCitizensModel();
    AppealCitizensModel(int id, QString applicant, int categoryCitizensId, QString yearBirth, QString contact, QString medicalOrganizationId, QString typeRequestId, QString description, QString dateRequest,
                        QString transmitted, QString result, QString tableUsersId, QString signClosure, QString anonymousAppeal, QString closingDate, QString comments);
    AppealCitizensModel(QString typeRequestId, QString dateRequest,QString tableUsersId);
};

#endif // APPEALCITIZENSMODEL_H
