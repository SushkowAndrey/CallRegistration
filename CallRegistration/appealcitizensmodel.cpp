#include "appealcitizensmodel.h"

AppealCitizensModel::AppealCitizensModel(){}

AppealCitizensModel::AppealCitizensModel(int id, QString applicant, int categoryCitizensId, QString yearBirth, QString contact, int medicalOrganizationId, int typeRequestId,
                                         QString description, QString dateRequest, QString transmitted, QString result, int tableUsersId,
                                         int signClosure, int anonymousAppeal, QString closingDate, QString comments)
{
    this->id=id;
    this->applicant=applicant;
    this->categoryCitizensId=categoryCitizensId;
    this->yearBirth=yearBirth;
    this->contact=contact;
    this->medicalOrganizationId=medicalOrganizationId;
    this->typeRequestId=typeRequestId;
    this->description=description;
    this->dateRequest=dateRequest;
    this->transmitted=transmitted;
    this->result=result;
    this->tableUsersId=tableUsersId;
    this->signClosure=signClosure;
    this->anonymousAppeal=anonymousAppeal;
    this->closingDate=closingDate;
    this->comments=comments;
}

AppealCitizensModel::AppealCitizensModel(QString applicant, int categoryCitizensId, QString yearBirth, QString contact, int medicalOrganizationId, int typeRequestId,
                                         QString description, QString dateRequest, QString transmitted, QString result, int tableUsersId,
                                         int signClosure, int anonymousAppeal, QString closingDate, QString comments)
{
    this->applicant=applicant;
    this->categoryCitizensId=categoryCitizensId;
    this->yearBirth=yearBirth;
    this->contact=contact;
    this->medicalOrganizationId=medicalOrganizationId;
    this->typeRequestId=typeRequestId;
    this->description=description;
    this->dateRequest=dateRequest;
    this->transmitted=transmitted;
    this->result=result;
    this->tableUsersId=tableUsersId;
    this->signClosure=signClosure;
    this->anonymousAppeal=anonymousAppeal;
    this->closingDate=closingDate;
    this->comments=comments;
}

AppealCitizensModel::AppealCitizensModel(int typeRequestId, QString dateRequest, int tableUsersId)
{
    this->typeRequestId=typeRequestId;
    this->dateRequest=dateRequest;
    this->tableUsersId=tableUsersId;
}
