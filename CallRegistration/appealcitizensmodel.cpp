#include "appealcitizensmodel.h"

AppealCitizensModel::AppealCitizensModel(){}

AppealCitizensModel::AppealCitizensModel(int id, QString applicant, int categoryCitizensId, QString yearBirth, QString contact, QString medicalOrganizationId, QString typeRequestId,
                                         QString description, QString dateRequest, QString transmitted, QString result, QString tableUsersId,
                                         QString signClosure, QString anonymousAppeal, QString closingDate, QString comments)
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

AppealCitizensModel::AppealCitizensModel(QString typeRequestId, QString dateRequest,QString tableUsersId)
{
    this->typeRequestId=typeRequestId;
    this->dateRequest=dateRequest;
    this->tableUsersId=tableUsersId;
}
