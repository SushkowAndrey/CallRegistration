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
    int medicalOrganizationId;//медицинская организация
    int typeRequestId;//тип обращения
    QString description; //описание
    QString dateRequest; //дата обращения
    QString transmitted; //кому передано
    QString result;//результат
    int tableUsersId;//кто принял
    int signClosure;//признак закрытия
    int anonymousAppeal;//анонимное или нет
    QString closingDate;//дата закрытия
    QString comments;//комментарий
public:
    AppealCitizensModel();
    AppealCitizensModel(int id, QString applicant, int categoryCitizensId, QString yearBirth, QString contact, int medicalOrganizationId, int typeRequestId, QString description, QString dateRequest,
                        QString transmitted, QString result, int tableUsersId, int signClosure, int anonymousAppeal, QString closingDate, QString comments);
    AppealCitizensModel(QString applicant, int categoryCitizensId, QString yearBirth, QString contact, int medicalOrganizationId, int typeRequestId, QString description, QString dateRequest,
                        QString transmitted, QString result, int tableUsersId, int signClosure, int anonymousAppeal, QString closingDate, QString comments);
    AppealCitizensModel(int typeRequestId, QString dateRequest,int tableUsersId);
};

#endif // APPEALCITIZENSMODEL_H
