#ifndef APPEALCITIZENSMODEL_H
#define APPEALCITIZENSMODEL_H

#include <QString>
#include <QDate>

class AppealCitizensModel
{
public:
    QString id;
    QString applicant; //ФИО заявителя
    QString categoryCitizensId;//категория заявителя
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
    AppealCitizensModel(QString id, QString applicant, QString categoryCitizensId, QString yearBirth, QString contact, QString medicalOrganizationId, QString typeRequestId, QString description, QString dateRequest,
                        QString transmitted, QString result, QString tableUsersId, QString signClosure, QString anonymousAppeal, QString closingDate, QString comments);
};

#endif // APPEALCITIZENSMODEL_H
