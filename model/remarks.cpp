#include "remarks.h"

Remarks::Remarks(TextField* problemId, TextField* problemDescription, TextField* sanctionId, TextField* sanctionDescription, TextField* factoryPerception)
{
    this->factoryPerception=factoryPerception;
    this->problemDescription=problemDescription;
    this->problemId=problemId;
    this->sanctionDescription=sanctionDescription;
    this->sanctionId=sanctionId;
}
