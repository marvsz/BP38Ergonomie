#ifndef DBCONSTANTS_H
#define DBCONSTANTS_H

#include <QString>
#include <QStringList>
#include <QList>
#include <QVariant>

enum DB_TABLES {ANALYST, EMPLOYER, CORPORATION, FACTORY, RECORDING};

class DBConstants
{
public:
    DBConstants();

    //Analyst
    static const QString TBL_ANALYST;
    static const QString COL_ANALYST_ID;
    static const QString COL_ANALYST_LASTNAME;
    static const QString COL_ANALYST_FIRSTNAME;
    static const QString COL_ANALYST_EXPERIENCE;
    static const QString COL_ANALYST_EMPLOYER_ID;
    static const QString COL_ANALYST_CORPORATION_ID;
    static const QStringList LIST_ANALYST_COLS;
    static const QList<QVariant::Type> LIST_ANALYST_TYPES;

    //Employer
    static const QString TBL_EMPLOYER;
    static const QString COL_EMPLOYER_ID;
    static const QString COL_EMPLOYER_NAME;
    static const QStringList LIST_EMPLOYER_COLS;
    static const QList<QVariant::Type> LIST_EMPLOYER_TYPES;

    //Corporation
    static const QString TBL_CORPORATION;
    static const QString COL_CORPORATION_ID;
    static const QString COL_CORPORATION_NAME;
    static const QString COL_CORPORATION_BRANCH_OF_INDUSTRY_ID;

    //Factory
    static const QString TBL_FACTORY;
    static const QString COL_FACTORY_ID;
    static const QString COL_FACTORY_NAME;
    static const QString COL_FACTORY_STREET;
    static const QString COL_FACTORY_ZIP;
    static const QString COL_FACTORY_CITY;
    static const QString COL_FACTORY_COUNTRY;
    static const QString COL_FACTORY_CONTACT_PERSON;
    static const QString COL_FACTORY_HEADCOUNT;
    static const QString COL_FACTORY_CORPORATION_ID;

    //Recording
    static const QString TBL_RECORDING;
    static const QString COL_RECORDING_ID;
    static const QString COL_RECORDING_START;
    static const QString COL_RECORDING_END;
    static const QString COL_RECORDING_FACTORY_ID;
    static const QString COL_RECORDING_ANALYST_ID;

};

#endif // DBCONSTANTS_H
