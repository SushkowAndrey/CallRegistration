#include "appealcitizensmodel.h"

AppealCitizensModel::AppealCitizensModel(){}

AppealCitizensModel::AppealCitizensModel(QString id, QString applicant, QString categoryCitizensId, QString yearBirth, QString contact, QString medicalOrganizationId, QString typeRequestId,
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
