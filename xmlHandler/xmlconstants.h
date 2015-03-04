#ifndef XMLCONSTANTS_H
#define XMLCONSTANTS_H

#include <QString>

class XMLConstants
{
public:
    //Transportation constants
    static const QString FILENAME_TRANSPORTATIONS;
    static const QString TRANSPORTATIONS;
    static const QString TRANSPORTATION;
    static const QString TRANSPORTATION_NAME;
    static const QString TRANSPORTATION_FIXED_ROLLER;
    static const QString TRANSPORTATION_BRAKES;
    static const QString TRANSPORTATION_MAX_LOAD;
    static const QString TRANSPORTATION_EMPTY_WEIGHT;

    //Equipment constants
    static const QString FILENAME_EQUIPMENTS;
    static const QString EQUIPMENTS;
    static const QString EQUIPMENT;
    static const QString EQUIPMENT_NAME;
    static const QString EQUIPMENT_RECOIL_COUNT;
    static const QString EQUIPMENT_RECOIL_INTENSITY;
    static const QString EQUIPMENT_VIBRATION_COUNT;
    static const QString EQUIPMENT_VIBRATION_INTENSITY;

    //Product constants
    static const QString FILENAME_PRODUCTS;
    static const QString PRODUCTS;
    static const QString PRODUCT;
    static const QString PRODUCT_NAME;
    static const QString PRODUCT_NUMBER;
    static const QString PRODUCT_TOTAL_PERCENTAGE;

    //Employee constants
    static const QString FILENAME_EMPLOYEES;
    static const QString EMPLOYEES;
    static const QString EMPLOYEE;
    static const QString EMPLOYEE_STAFF_NUMBER;
    static const QString EMPLOYEE_AGE;
    static const QString EMPLOYEE_GENDER;
    static const QString EMPLOYEE_HEIGHT;
    static const QString EMPLOYEE_NOTE;
    //Employee Body measurement constants
    static const QString EMPLOYEE_BODY_MEASUREMENT;
    static const QString EMPLOYEE_BODY_MEASUREMENT_HEAD_NECK_HEIGHT;
    static const QString EMPLOYEE_BODY_MEASUREMENT_SHOULDER_WIDTH;
    static const QString EMPLOYEE_BODY_MEASUREMENT_SHOULDER_WIDTH_BIACROMIAL;
    static const QString EMPLOYEE_BODY_MEASUREMENT_SHOULDER_WIDTH_BIDELTOID;
    static const QString EMPLOYEE_BODY_MEASUREMENT_UPPER_ARM_LENGTH;
    static const QString EMPLOYEE_BODY_MEASUREMENT_FOREARM_LENGTH;
    static const QString EMPLOYEE_BODY_MEASUREMENT_HAND_LENGTH_GRIP_AXIS;
    static const QString EMPLOYEE_BODY_MEASUREMENT_TORSO_HEIGHT;
    static const QString EMPLOYEE_BODY_MEASUREMENT_THIGHT_HEIGHT;
    static const QString EMPLOYEE_BODY_MEASUREMENT_TIBIAL_HEIGHT;
    static const QString EMPLOYEE_BODY_MEASUREMENT_FOOT_LENGTH;

    //Workplace constants
    static const QString FILENAME_WORKPLACES;
    static const QString WORKPLACES;
    static const QString WORKPLACE;
    static const QString WORKPLACE_NAME;
    static const QString WORKPLACE_DESCRIPTION;
    static const QString WORKPLACE_PERCENTAGE_WOMAN;
    static const QString WORKPLACE_CODE;
    static const QString WORKPLACE_CYCLE_TIME;
    static const QString WORKPLACE_SETUP_TIME;
    static const QString WORKPLACE_BASIC_TIME;
    static const QString WORKPLACE_REST_TIME;
    static const QString WORKPLACE_ALLOWANCE_TIME;
    //Workplace activitie constants
    static const QString WORKPLACE_ACTIVITIES;
    static const QString WORKPLACE_ACTIVITY;
    static const QString WORKPLACE_ACTIVITY_DESCRIPTION;
    static const QString WORKPLACE_ACTIVITY_REPETITIONS;
    static const QString WORKPLACE_ACTIVITY_PRODUCTNAME;
};

#endif // XMLCONSTANTS_H
