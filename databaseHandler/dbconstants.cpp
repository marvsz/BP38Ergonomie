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
const QStringList DBConstants::LIST_CORPORATION_COLS = QStringList()<<DBConstants::COL_CORPORATION_ID<<DBConstants::COL_CORPORATION_NAME;
const QList<QVariant::Type> DBConstants::LIST_CORPORATION_TYPES = QList<QVariant::Type>()<<QVariant::Int<<QVariant::String;

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
const QStringList DBConstants::LIST_FACTORY_COLS = QStringList()<<DBConstants::COL_FACTORY_ID<<DBConstants::COL_FACTORY_NAME<<DBConstants::COL_FACTORY_STREET<<DBConstants::COL_FACTORY_ZIP<<DBConstants::COL_FACTORY_CITY<<DBConstants::COL_FACTORY_COUNTRY<<DBConstants::COL_FACTORY_CONTACT_PERSON<<DBConstants::COL_FACTORY_HEADCOUNT<<DBConstants::COL_FACTORY_CORPORATION_ID;
const QList<QVariant::Type> DBConstants::LIST_FACTORY_TYPES = QList<QVariant::Type>()<<QVariant::Int<<QVariant::String<<QVariant::String<<QVariant::Int<<QVariant::String<<QVariant::String<<QVariant::String<<QVariant::Int<<QVariant::Int;

//Recording
const QString DBConstants::TBL_RECORDING = "Recording";
const QString DBConstants::COL_RECORDING_ID = "recording_ID";
const QString DBConstants::COL_RECORDING_START = "recording_start";
const QString DBConstants::COL_RECORDING_END = "recording_end";
const QString DBConstants::COL_RECORDING_FACTORY_ID = "factory_ID";
const QString DBConstants::COL_RECORDING_ANALYST_ID = "analyst_ID";
const QStringList DBConstants::LIST_RECORDING_COLS = QStringList()<<DBConstants::COL_RECORDING_ID<<DBConstants::COL_RECORDING_START<<DBConstants::COL_RECORDING_END<<DBConstants::COL_RECORDING_FACTORY_ID<<DBConstants::COL_RECORDING_ANALYST_ID;
const QList<QVariant::Type> DBConstants::LIST_RECORDING_TYPES = QList<QVariant::Type>()<<QVariant::Int<<QVariant::String<<QVariant::String<<QVariant::Int<<QVariant::Int;

//Recording observes Line
const QString DBConstants::TBL_RECORDING_OB_LINE = "Recording_observes_Line";
const QString DBConstants::COL_RECORDING_OB_LINE_RECORDING_ID = "recording_ID";
const QString DBConstants::COL_RECORDING_OB_LINE_LINE_ID = "line_ID";
const QStringList DBConstants::LIST_RECORDING_OB_LINE_COLS = QStringList()<<DBConstants::COL_RECORDING_OB_LINE_RECORDING_ID<<DBConstants::COL_RECORDING_OB_LINE_LINE_ID;
const QList<QVariant::Type> DBConstants::LIST_RECORDING_OB_LINE_TYPES = QList<QVariant::Type>()<<QVariant::Int<<QVariant::Int;

//Recording observes Workplace
const QString DBConstants::TBL_RECORDING_OB_WORKPLACE = "Recording_observes_Workplace";
const QString DBConstants::COL_RECORDING_OB_WORKPLACE_RECORDING_ID = "recording_ID";
const QString DBConstants::COL_RECORDING_OB_WORKPLACE_WORKPLACE_ID = "workplace_ID";
const QStringList DBConstants::LIST_RECORDING_OB_WORKPLACE_COLS = QStringList()<<DBConstants::COL_RECORDING_OB_WORKPLACE_RECORDING_ID<<DBConstants::COL_RECORDING_OB_WORKPLACE_WORKPLACE_ID;
const QList<QVariant::Type> DBConstants::LIST_RECORDING_OB_WORKPLACE_TYPES = QList<QVariant::Type>()<<QVariant::Int<<QVariant::Int;

//Line
const QString DBConstants::TBL_LINE = "Line";
const QString DBConstants::COL_LINE_ID = "line_ID";
const QString DBConstants::COL_LINE_NAME = "line_name";
const QString DBConstants::COL_LINE_DESCRIPTION = "line_description";
const QString DBConstants::COL_LINE_NUMBER_OF_WORKPLACES = "number_of_workplaces";
const QString DBConstants::COL_LINE_FACTORY_ID = "factory_ID";
const QStringList DBConstants::LIST_LINE_COLS = QStringList()<<DBConstants::COL_LINE_ID<<DBConstants::COL_LINE_NAME<<DBConstants::COL_LINE_DESCRIPTION<<DBConstants::COL_LINE_NUMBER_OF_WORKPLACES<<DBConstants::COL_LINE_FACTORY_ID;
const QList<QVariant::Type> DBConstants::LIST_LINE_TYPES = QList<QVariant::Type>()<<QVariant::Int<<QVariant::String<<QVariant::String<<QVariant::Int<<QVariant::Int;

//Workplace
const QString DBConstants::TBL_WORKPLACE = "Workplace";
const QString DBConstants::COL_WORKPLACE_ID = "workplace_ID";
const QString DBConstants::COL_WORKPLACE_NAME = "workplace_name";
const QString DBConstants::COL_WORKPLACE_DESCRIPTION = "workplace_description";
const QString DBConstants::COL_WORKPLACE_PERCENTAGE_WOMAN = "percentage_woman";
const QString DBConstants::COL_WORKPLACE_LINE_ID = "line_ID";
const QString DBConstants::COL_WORKPLACE_CODE = "code";
const QString DBConstants::COL_WORKPLACE_CYCLE_TIME = "cycle_time";
const QString DBConstants::COL_WORKPLACE_SETUP_TIME = "setup_time";
const QString DBConstants::COL_WORKPLACE_BASIC_TIME = "basic_time";
const QString DBConstants::COL_WORKPLACE_REST_TIME = "rest_time";
const QString DBConstants::COL_WORKPLACE_ALLOWANCE_TIME = "allowance_time";
const QString DBConstants::COL_WORKPLACE_BODY_MEASUREMENT_ID = "body_measurement_ID";
const QStringList DBConstants::LIST_WORKPLACE_COLS = QStringList()<<DBConstants::COL_WORKPLACE_ID<<DBConstants::COL_WORKPLACE_NAME<<DBConstants::COL_WORKPLACE_DESCRIPTION<<DBConstants::COL_WORKPLACE_PERCENTAGE_WOMAN<<DBConstants::COL_WORKPLACE_LINE_ID<<DBConstants::COL_WORKPLACE_CODE<<DBConstants::COL_WORKPLACE_CYCLE_TIME<<DBConstants::COL_WORKPLACE_SETUP_TIME<<DBConstants::COL_WORKPLACE_BASIC_TIME<<DBConstants::COL_WORKPLACE_REST_TIME<<DBConstants::COL_WORKPLACE_ALLOWANCE_TIME;
const QList<QVariant::Type> DBConstants::LIST_WORKPLACE_TYPES = QList<QVariant::Type>()<<QVariant::Int<<QVariant::String<<QVariant::String<<QVariant::Double<<QVariant::Int<<QVariant::String<<QVariant::Int<<QVariant::Int<<QVariant::Int<<QVariant::Int<<QVariant::Int;


//Comment
const QString DBConstants::TBL_COMMENT = "Comment";
const QString DBConstants::COL_COMMENT_ID = "comment_ID";
const QString DBConstants::COL_COMMENT_PROBLEM_NAME = "problem_name";
const QString DBConstants::COL_COMMENT_PROBLEM_DESCRIPTION = "problem_description";
const QString DBConstants::COL_COMMENT_MEASURE_NAME = "measure_name";
const QString DBConstants::COL_COMMENT_MEASURE_DESCRIPTION = "measure_description";
const QString DBConstants::COL_COMMENT_WORKER_PERCEPTION = "worker_perception";
const QString DBConstants::COL_COMMENT_WORKPLACE_ID = "workplace_ID";
const QStringList DBConstants::LIST_COMMENT_COLS = QStringList()<<DBConstants::COL_COMMENT_ID<<DBConstants::COL_COMMENT_PROBLEM_NAME<<DBConstants::COL_COMMENT_PROBLEM_DESCRIPTION<<DBConstants::COL_COMMENT_MEASURE_NAME<<DBConstants::COL_COMMENT_MEASURE_DESCRIPTION<<DBConstants::COL_COMMENT_WORKER_PERCEPTION<<DBConstants::COL_COMMENT_WORKPLACE_ID;
const QList<QVariant::Type> DBConstants::LIST_COMMENT_TYPES = QList<QVariant::Type>()<<QVariant::Int<<QVariant::String<<QVariant::String<<QVariant::String<<QVariant::String<<QVariant::String<<QVariant::Int;

//Employee
const QString DBConstants::TBL_EMPLOYEE = "Employee";
const QString DBConstants::COL_EMPLOYEE_ID = "employee_ID";
const QString DBConstants::COL_EMPLOYEE_STAFF_NUMBER = "staff_number";
const QString DBConstants::COL_EMPLOYEE_AGE = "age";
const QString DBConstants::COL_EMPLOYEE_HEIGHT = "height";
const QString DBConstants::COL_EMPLOYEE_NOTE = "note";
const QStringList DBConstants::LIST_EMPLOYEE_COLS = QStringList()<<DBConstants::COL_EMPLOYEE_ID<<DBConstants::COL_EMPLOYEE_STAFF_NUMBER<<DBConstants::COL_EMPLOYEE_AGE<<DBConstants::COL_EMPLOYEE_HEIGHT<<DBConstants::COL_EMPLOYEE_NOTE;
const QList<QVariant::Type> DBConstants::LIST_EMPLOYEE_TYPES = QList<QVariant::Type>()<<QVariant::Int<<QVariant::String<<QVariant::String<<QVariant::String<<QVariant::Int<<QVariant::String;

//Employee_works_Shift
const QString DBConstants::TBL_EMPLOYEE_WORKS_SHIFT = "Employee_works_Shift";
const QString DBConstants::COL_EMPLOYEE_WORKS_SHIFT_EMPLOYEE_ID = "employee_ID";
const QString DBConstants::COL_EMPLOYEE_WORKS_SHIFT_SHIFT_ID = "shift_ID";
const QStringList DBConstants::LIST_EMPlOYEE_WORKS_SHIFT_COLS = QStringList()<<DBConstants::COL_EMPLOYEE_WORKS_SHIFT_EMPLOYEE_ID<<DBConstants::COL_EMPLOYEE_WORKS_SHIFT_SHIFT_ID;
const QList<QVariant::Type> DBConstants::LIST_EMPLOYEE_WORKS_SHIFT_TYPES = QList<QVariant::Type>()<<QVariant::Int<<QVariant::Int;

//Product
const QString DBConstants::TBL_PRODUCT = "Product";
const QString DBConstants::COL_PRODUCT_ID = "product_ID";
const QString DBConstants::COL_PRODUCT_NUMBER = "product_number";
const QString DBConstants::COL_PRODUCT_NAME = "product_name";
const QString DBConstants::COL_PRODUCT_TOTAL_PERCENTAGE = "total_percentage";
const QStringList DBConstants::LIST_PRODUCT_COLS = QStringList()<<DBConstants::COL_PRODUCT_ID<<DBConstants::COL_PRODUCT_NUMBER<<DBConstants::COL_PRODUCT_NAME<<DBConstants::COL_PRODUCT_TOTAL_PERCENTAGE;
const QList<QVariant::Type> DBConstants::LIST_PRODUCT_TYPES = QList<QVariant::Type>()<<QVariant::Int<<QVariant::String<<QVariant::String<<QVariant::Double;

//Shift
const QString DBConstants::TBL_SHIFT = "Shift";
const QString DBConstants::COL_SHIFT_ID = "shift_ID";
const QString DBConstants::COL_SHIFT_ROTATION_SHIFT_ID = "rotation_shift_ID";
const QString DBConstants::COL_SHIFT_TYPE = "type";
const QString DBConstants::COL_SHIFT_START = "start";
const QString DBConstants::COL_SHIFT_END = "end";
const QStringList DBConstants::LIST_SHIFT_COLS = QStringList()<<DBConstants::COL_SHIFT_ID<<DBConstants::COL_SHIFT_ROTATION_SHIFT_ID<<DBConstants::COL_SHIFT_TYPE<<DBConstants::COL_SHIFT_START<<DBConstants::COL_SHIFT_END;
const QList<QVariant::Type> DBConstants::LIST_SHIFT_TYPES = QList<QVariant::Type>()<<QVariant::Int<<QVariant::Int<<QVariant::String<<QVariant::String<<QVariant::String;

//Break
const QString DBConstants::TBL_BREAK = "Break";
const QString DBConstants::COL_BREAK_ID = "break_ID";
const QString DBConstants::COL_BREAK_START = "break_start";
const QString DBConstants::COL_BREAK_END = "break_end";
const QString DBConstants::COL_BREAK_SHIFT_ID = "shift_ID";
const QString DBConstants::COL_BREAK_EMPLOYEE_ID = "employee_ID";
const QStringList DBConstants::LIST_BREAK_COLS = QStringList()<<DBConstants::COL_BREAK_ID<<DBConstants::COL_BREAK_START<<DBConstants::COL_BREAK_END<<DBConstants::COL_BREAK_SHIFT_ID<<DBConstants::COL_BREAK_EMPLOYEE_ID;
const QList<QVariant::Type> DBConstants::LIST_BREAK_TYPES = QList<QVariant::Type>()<<QVariant::Int<<QVariant::String<<QVariant::String<<QVariant::Int<<QVariant::Int;

DBConstants::DBConstants()
{
}
