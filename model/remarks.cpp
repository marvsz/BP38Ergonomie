#include "remarks.h"

Remarks::Remarks(QString* problemId, QString* problemDescription, QString* sanctionId, QString* sanctionDescription, QString* factoryPerception)
{
    this->factoryPerception=factoryPerception;
    this->problemDescription=problemDescription;
    this->problemId=problemId;
    this->sanctionDescription=sanctionDescription;
    this->sanctionId=sanctionId;
}
