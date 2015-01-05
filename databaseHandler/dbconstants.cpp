#include "dbconstants.h"



//Analyst
const QString DBConstants::TBL_ANALYST = "Analyst";
const QString DBConstants::COL_ANALYST_ID = "analyst_ID";
const QString DBConstants::COL_ANALYST_LASTNAME = "analyst_last_name";
const QString DBConstants::COL_ANALYST_FIRSTNAME = "analyst_first_name";
const QString DBConstants::COL_ANALYST_EXPERIENCE = "analyst_experience";
const QString DBConstants::COL_ANALYST_EMPLOYER_ID = "employer_ID";
const QString DBConstants::COL_ANALYST_CORPORATION_ID = "corporation_ID";
const QStringList DBConstants::LIST_ANALYST_COLS = QStringList()<<DBConstants::COL_ANALYST_ID<<DBConstants::COL_ANALYST_LASTNAME<<DBConstants::COL_ANALYST_FIRSTNAME<<DBConstants::COL_ANALYST_EXPERIENCE<<DBConstants::COL_ANALYST_EMPLOYER_ID;
const QList<QVariant::Type> DBConstants::LIST_ANALYST_TYPES = QList<QVariant::Type>()<<QVariant::Int<<QVariant::String<<QVariant::String<<QVariant::String<<QVariant::Int;

//Employer
const QString DBConstants::TBL_EMPLOYER = "Employer";
const QString DBConstants::COL_EMPLOYER_ID = "employer_ID";
const QString DBConstants::COL_EMPLOYER_NAME = "employer_name";
const QStringList DBConstants::LIST_EMPLOYER_COLS = QStringList()<<DBConstants::COL_EMPLOYER_ID<<DBConstants::COL_EMPLOYER_NAME;
const QList<QVariant::Type> DBConstants::LIST_EMPLOYER_TYPES = QList<QVariant::Type>()<<QVariant::Int<<QVariant::String;

//Corporation
const QString DBConstants::TBL_CORPORATION = "Corporation";
const QString DBConstants::COL_CORPORATION_ID = "corporation_ID";
const QString DBConstants::COL_CORPORATION_NAME = "corporation_name";
const QString DBConstants::COL_CORPORATION_BRANCH_OF_INDUSTRY_ID = "branch_of_industry_ID";

//Factory
const QString DBConstants::TBL_FACTORY = "Factory";
const QString DBConstants::COL_FACTORY_ID = "factory_ID";
const QString DBConstants::COL_FACTORY_NAME = "factory_name";
const QString DBConstants::COL_FACTORY_STREET = "factory_street";
const QString DBConstants::COL_FACTORY_ZIP = "factory_zip";
const QString DBConstants::COL_FACTORY_CITY = "factory_city";
const QString DBConstants::COL_FACTORY_COUNTRY = "factory_country";
const QString DBConstants::COL_FACTORY_CONTACT_PERSON = "factory_contact_person";
const QString DBConstants::COL_FACTORY_HEADCOUNT = "factory_headcount";
const QString DBConstants::COL_FACTORY_CORPORATION_ID = "corporation_ID";

//Recording
const QString DBConstants::TBL_RECORDING = "Recording";
const QString DBConstants::COL_RECORDING_ID = "recording_ID";
const QString DBConstants::COL_RECORDING_START = "recording_start";
const QString DBConstants::COL_RECORDING_END = "recording_end";
const QString DBConstants::COL_RECORDING_FACTORY_ID = "factory_ID";
const QString DBConstants::COL_RECORDING_ANALYST_ID = "analyst_ID";

DBConstants::DBConstants()
{
}
