#ifndef DBCONSTANTS_H
#define DBCONSTANTS_H

#include <QString>

enum DB_TABLES {ANALYST};

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
    static const QString COL_ANALYST_EMPLOYER;
    static const QString COL_ANALYST_CORPORATION;
};

#endif // DBCONSTANTS_H
