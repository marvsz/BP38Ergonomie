#ifndef DBCONSTANTS_H
#define DBCONSTANTS_H

#include <QString>
#include <QStringList>
#include <QList>
#include <QVariant>

enum DB_TABLES {ANALYST, EMPLOYER, CORPORATION, FACTORY, RECORDING,
                RECORDING_OBSERVES_LINE, RECORDING_OBSERVES_WORKPLACE, LINE, WORKPLACE};

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
    static const QStringList LIST_CORPORATION_COLS;
    static const QList<QVariant::Type> LIST_CORPORATION_TYPES;

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
    static const QStringList LIST_FACTORY_COLS;
    static const QList<QVariant::Type> LIST_FACTORY_TYPES;

    //Recording
    static const QString TBL_RECORDING;
    static const QString COL_RECORDING_ID;
    static const QString COL_RECORDING_START;
    static const QString COL_RECORDING_END;
    static const QString COL_RECORDING_FACTORY_ID;
    static const QString COL_RECORDING_ANALYST_ID;
    static const QStringList LIST_RECORDING_COLS;
    static const QList<QVariant::Type> LIST_RECORDING_TYPES;

    //Recording observes Line
    static const QString TBL_RECORDING_OB_LINE;
    static const QString COL_RECORDING_OB_LINE_RECORDING_ID;
    static const QString COL_RECORDING_OB_LINE_LINE_ID;
    static const QStringList LIST_RECORDING_OB_LINE_COLS;
    static const QList<QVariant::Type> LIST_RECORDING_OB_LINE_TYPES;

    //Recording observes Workplace
    static const QString TBL_RECORDING_OB_WORKPLACE;
    static const QString COL_RECORDING_OB_WORKPLACE_RECORDING_ID;
    static const QString COL_RECORDING_OB_WORKPLACE_WORKPLACE_ID;
    static const QStringList LIST_RECORDING_OB_WORKPLACE_COLS;
    static const QList<QVariant::Type> LIST_RECORDING_OB_WORKPLACE_TYPES;

    //Line
    static const QString TBL_LINE;
    static const QString COL_LINE_ID;
    static const QString COL_LINE_NAME;
    static const QString COL_LINE_DESCRIPTION;
    static const QString COL_LINE_NUMBER_OF_WORKPLACES;
    static const QString COL_LINE_FACTORY_ID;
    static const QStringList LIST_LINE_COLS;
    static const QList<QVariant::Type> LIST_LINE_TYPES;

    //Workplace
    static const QString TBL_WORKPLACE;
    static const QString COL_WORKPLACE_ID;
    static const QString COL_WORKPLACE_NAME;
    static const QString COL_WORKPLACE_DESCRIPTION;
    static const QString COL_WORKPLACE_PERCENTAGE_WOMAN;
    static const QString COL_WORKPLACE_LINE_ID;
    static const QString COL_WORKPLACE_CODE;
    static const QString COL_WORKPLACE_CYCLE_TIME;
    static const QString COL_WORKPLACE_SETUP_TIME;
    static const QString COL_WORKPLACE_BASIC_TIME;
    static const QString COL_WORKPLACE_REST_TIME;
    static const QString COL_WORKPLACE_ALLOWANCE_TIME;
    static const QString COL_WORKPLACE_BODY_MEASUREMENT_ID;
    static const QStringList LIST_WORKPLACE_COLS;
    static const QList<QVariant::Type> LIST_WORKPLACE_TYPES;

};

#endif // DBCONSTANTS_H
