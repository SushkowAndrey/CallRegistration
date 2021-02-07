#ifndef APPEALCITIZENSMODEL_H
#define APPEALCITIZENSMODEL_H

#include <QString>
#include <QDate>

class AppealCitizensModel
{
    int id;
    QString applicant; //ФИО заявителя
    int categoryCitizensId;//категория заявителя
    QString yearBirth;//год рождения
    QString contact;//адрес и телефон
    int medicalOrganizationId;//медицинская организация
    int typeRequestId;//тип обращения
    QString description; //описание
    QDate dateRequest; //дата обращения
    QString transmitted; //кому передано
    QString result;//результат
    int tableUsersId;//кто принял
    bool signClosure;//признак закрытия
    bool anonymousAppeal;//анонимное или нет
    QDate closingDate;//дата закрытия
    QString comments;//комментарий
public:
    AppealCitizensModel();
};

#endif // APPEALCITIZENSMODEL_H
