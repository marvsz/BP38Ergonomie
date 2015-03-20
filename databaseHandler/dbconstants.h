#ifndef DBCONSTANTS_H
#define DBCONSTANTS_H

#include <QString>
#include <QList>
#include <QVariant>
#include <QHash>


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
    static const QHash<QString, QVariant::Type> HASH_ANALYST_TYPES;

    //Employer
    static const QString TBL_EMPLOYER;
    static const QString COL_EMPLOYER_ID;
    static const QString COL_EMPLOYER_NAME;
    static const QHash<QString, QVariant::Type> HASH_EMPLOYER_TYPES;

    //Corporation
    static const QString TBL_CORPORATION;
    static const QString COL_CORPORATION_ID;
    static const QString COL_CORPORATION_NAME;
    static const QString COL_CORPORATION_BRANCH_OF_INDUSTRY_ID;
    static const QHash<QString, QVariant::Type> HASH_CORPORATION_TYPES;

    //Branch of Industry
    static const QString TBL_BRANCH_OF_INDUSTRY;
    static const QString COL_BRANCH_OF_INDUSTRY_ID;
    static const QString COL_BRANCH_OF_INDUSTRY_NAME;
    static const QString COL_BRANCH_OF_INDUSTRY_DESCRIPTION;
    static const QHash<QString, QVariant::Type> HASH_BRANCH_OF_INDUSTRY_TYPES;

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
    static const QHash<QString, QVariant::Type> HASH_FACTORY_TYPES;

    //Recording
    static const QString TBL_RECORDING;
    static const QString COL_RECORDING_ID;
    static const QString COL_RECORDING_START;
    static const QString COL_RECORDING_END;
    static const QString COL_RECORDING_FACTORY_ID;
    static const QString COL_RECORDING_ANALYST_ID;
    static const QHash<QString, QVariant::Type> HASH_RECORDING_TYPES;

    //Recording observes Line
    static const QString TBL_RECORDING_OB_LINE;
    static const QString COL_RECORDING_OB_LINE_RECORDING_ID;
    static const QString COL_RECORDING_OB_LINE_LINE_ID;
    static const QHash<QString, QVariant::Type> HASH_RECORDING_OB_LINE_TYPES;

    //Recording observes Workplace
    static const QString TBL_RECORDING_OB_WORKPLACE;
    static const QString COL_RECORDING_OB_WORKPLACE_RECORDING_ID;
    static const QString COL_RECORDING_OB_WORKPLACE_WORKPLACE_ID;
    static const QHash<QString, QVariant::Type> HASH_RECORDING_OB_WORKPLACE_TYPES;

    //Line
    static const QString TBL_LINE;
    static const QString COL_LINE_ID;
    static const QString COL_LINE_NAME;
    static const QString COL_LINE_DESCRIPTION;
    static const QString COL_LINE_NUMBER_OF_WORKPLACES;
    static const QString COL_LINE_FACTORY_ID;
    static const QHash<QString, QVariant::Type> HASH_LINE_TYPES;

    //Workplace
    static const QString TBL_WORKPLACE;
    static const QString COL_WORKPLACE_ID;
    static const QString COL_WORKPLACE_NAME;
    static const QString COL_WORKPLACE_DESCRIPTION;
    static const QString COL_WORKPLACE_PERCENTAGE_WOMAN;
    static const QString COL_WORKPLACE_LINE_ID;
    static const QString COL_WORKPLACE_EMPLOYEE_ID;
    static const QString COL_WORKPLACE_CODE;
    static const QString COL_WORKPLACE_CYCLE_TIME;
    static const QString COL_WORKPLACE_SETUP_TIME;
    static const QString COL_WORKPLACE_BASIC_TIME;
    static const QString COL_WORKPLACE_REST_TIME;
    static const QString COL_WORKPLACE_ALLOWANCE_TIME;
    static const QHash<QString, QVariant::Type> HASH_WORKPLACE_TYPES;

    //Comment
    static const QString TBL_COMMENT;
    static const QString COL_COMMENT_ID;
    static const QString COL_COMMENT_PROBLEM_NAME;
    static const QString COL_COMMENT_PROBLEM_DESCRIPTION;
    static const QString COL_COMMENT_MEASURE_NAME;
    static const QString COL_COMMENT_MEASURE_DESCRIPTION;
    static const QString COL_COMMENT_WORKER_PERCEPTION;
    static const QString COL_COMMENT_WORKPLACE_ID;
    static const QHash<QString, QVariant::Type> HASH_COMMENT_TYPES;

    //Employee
    static const QString TBL_EMPLOYEE;
    static const QString COL_EMPLOYEE_ID;
    static const QString COL_EMPLOYEE_STAFF_NUMBER;
    static const QString COL_EMPLOYEE_AGE;
    static const QString COL_EMPLOYEE_GENDER;
    static const QString COL_EMPLOYEE_HEIGHT;
    static const QString COL_EMPLOYEE_NOTE;
    static const QString COL_EMPLOYEE_BODY_MEASUREMENT_ID;
    static const QHash<QString, QVariant::Type> HASH_EMPLOYEE_TYPES;

    //Body Measurement
    static const QString TBL_BODY_MEASUREMENT;
    static const QString COL_BODY_MEASUREMENT_ID;
    static const QString COL_BODY_MEASUREMENT_HEAD_NECK_HEIGHT;
    static const QString COL_BODY_MEASUREMENT_SHOULDER_WIDTH;
    static const QString COL_BODY_MEASUREMENT_SHOULDER_WIDTH_BIACROMIAL;
    static const QString COL_BODY_MEASUREMENT_SHOULDER_WIDTH_BIDELTOID;
    static const QString COL_BODY_MEASUREMENT_UPPER_ARM_LENGTH;
    static const QString COL_BODY_MEASUREMENT_FOREARM_LENGTH;
    static const QString COL_BODY_MEASUREMENT_HAND_LENGTH_GRIP_AXIS;
    static const QString COL_BODY_MEASUREMENT_TORSO_HEIGHT;
    static const QString COL_BODY_MEASUREMENT_THIGH_LENGTH;
    static const QString COL_BODY_MEASUREMENT_TIBIAL_HEIGHT;
    static const QString COL_BODY_MEASUREMENT_FOOT_LENGTH;
    static const QHash<QString, QVariant::Type> HASH_BODY_MEASUREMENT_TYPES;

    //Product
    static const QString TBL_PRODUCT;
    static const QString COL_PRODUCT_ID;
    static const QString COL_PRODUCT_NUMBER;
    static const QString COL_PRODUCT_NAME;
    static const QString COL_PRODUCT_TOTAL_PERCENTAGE;
    static const QHash<QString, QVariant::Type> HASH_PRODUCT_TYPES;

    //Activity
    static const QString TBL_ACTIVITY;
    static const QString COL_ACTIVITY_ID;
    static const QString COL_ACTIVITY_DESCRIPTION;
    static const QString COL_ACTIVITY_REPETITIONS;
    static const QString COL_ACTIVITY_PRODUCT_ID;
    static const QString COL_ACTIVITY_WORKPLACE_ID;
    static const QHash<QString, QVariant::Type> HASH_ACTIVITY_TYPES;

    //Body_Posture
    static const QString TBL_BODY_POSTURE;
    static const QString COL_BODY_POSTURE_ID;
    static const QString COL_BODY_POSTURE_HEAD_TILT;
    static const QString COL_BODY_POSTURE_HEAD_TILT_SIDEWAYS;
    static const QString COL_BODY_POSTURE_HEAD_TWIST;
    static const QString COL_BODY_POSTURE_ARM_OPENING_ANGLE_RIGHT;
    static const QString COL_BODY_POSTURE_ARM_OPENING_ANGLE_LEFT;
    static const QString COL_BODY_POSTURE_UPPER_ARM_ANGLE_RIGHT;
    static const QString COL_BODY_POSTURE_UPPER_ARM_ANGLE_LEFT;
    static const QString COL_BODY_POSTURE_UPPER_ARM_TWIST_RIGHT;
    static const QString COL_BODY_POSTURE_UPPER_ARM_TWIST_LEFT;
    static const QString COL_BODY_POSTURE_FOREARM_ANGLE_RIGHT;
    static const QString COL_BODY_POSTURE_FOREARM_ANGLE_LEFT;
    static const QString COL_BODY_POSTURE_FOREARM_TWIST_RIGHT;
    static const QString COL_BODY_POSTURE_FOREARM_TWIST_LEFT;
    static const QString COL_BODY_POSTURE_WRIST_ANGLE_RIGHT;
    static const QString COL_BODY_POSTURE_WRIST_ANGLE_SIDEWAYS_RIGHT;
    static const QString COL_BODY_POSTURE_WRIST_ANGLE_LEFT;
    static const QString COL_BODY_POSTURE_WRIST_ANGLE_SIDEWAYS_LEFT;
    static const QString COL_BODY_POSTURE_WRIST_MOVEMENT_RIGHT;
    static const QString COL_BODY_POSTURE_WRIST_MOVEMENT_LEFT;
    static const QString COL_BODY_POSTURE_TRUNK_TILT;
    static const QString COL_BODY_POSTURE_TRUNK_TILT_SIDEWAYS;
    static const QString COL_BODY_POSTURE_TRUNK_TWIST;
    static const QString COL_BODY_POSTURE_LEG_COUNT;
    static const QString COL_BODY_POSTURE_LEG_POSTURE;
    static const QString COL_BODY_POSTURE_HIP_ANGLE_RIGHT;
    static const QString COL_BODY_POSTURE_HIP_ANGLE_LEFT;
    static const QString COL_BODY_POSTURE_HIP_ANGLE_SIDEWAYS_LEFT;
    static const QString COL_BODY_POSTURE_HIP_ANGLE_SIDEWAYS_RIGHT;
    static const QString COL_BODY_POSTURE_HIP_TWIST_LEFT;
    static const QString COL_BODY_POSTURE_HIP_TWIST_RIGHT;
    static const QString COL_BODY_POSTURE_KNEE_ANGLE_RIGHT;
    static const QString COL_BODY_POSTURE_KNEE_ANGLE_LEFT;
    static const QString COL_BODY_POSTURE_ANKLE_ANGLE_RIGHT;
    static const QString COL_BODY_POSTURE_ANKLE_ANGLE_SIDEWAYS_RIGHT;
    static const QString COL_BODY_POSTURE_ANKLE_ANGLE_LEFT;
    static const QString COL_BODY_POSTURE_ANKLE_ANGLE_SIDEWAYS_LEFT;
    static const QHash<QString, QVariant::Type> HASH_BODY_POSTURE_TYPES;

    //Workprocess
    static const QString TBL_WORK_PROCESS;
    static const QString COL_WORK_PROCESS_ACTIVITY_ID;
    static const QString COL_WORK_PROCESS_ID;
    static const QString COL_WORK_PROCESS_TYPE;
    static const QString COL_WORK_PROCESS_DESCRIPTION;
    static const QString COL_WORK_PROCESS_BEGIN;
    static const QString COL_WORK_PROCESS_END;
    static const QString COL_WORK_PROCESS_MTM_CODE;
    static const QString COL_WORK_PROCESS_FREQUENCY;
    static const QString COL_WORK_PROCESS_IMPULSE_INTENSITY;
    static const QString COL_WORK_PROCESS_IMPULSE_COUNT;
    static const QString COL_WORK_PROCESS_WORKING_HEIGHT;
    static const QString COL_WORK_PROCESS_DISTANCE;
    static const QString COL_WORK_PROCESS_POSTURE_ID;
    static const QString COL_WORK_PROCESS_EQUIPMENT_ID;
    static const QString COL_WORK_PROCESS_CONDITION_ID;
    static const QString COL_WORK_PROCESS_APPLIED_FORCE_ID;
    static const QString COL_WORK_PROCESS_LOAD_HANDLING_ID;
    static const QHash<QString, QVariant::Type> HASH_WORK_PROCESS_TYPES;

    //Load_Handling_Type
    static const QString TBL_LOAD_HANDLING_TYPE;
    static const QString COL_LOAD_HANDLING_TYPE_ID;
    static const QString COL_LOAD_HANDLING_TYPE_NAME;
    static const QHash<QString, QVariant::Type> HASH_LOAD_HANDLING_TYPE_TYPES;

    //Load_Handling
    static const QString TBL_LOAD_HANDLING;
    static const QString COL_LOAD_HANDLING_ID;
    static const QString COL_LOAD_HANDLING_LOAD;
    static const QString COL_LOAD_HANDLING_DISTANCE;
    static const QString COL_LOAD_HANDLING_LOAD_HANDLING_TYPE_ID;
    static const QString COL_LOAD_HANDLING_TYPE_OF_GRASPING;
    static const QString COL_LOAD_HANDLING_TRANSPORTATION_ID;
    static const QHash<QString, QVariant::Type> HASH_LOAD_HANDLING_TYPES;

    //Applied_Force
    static const QString TBL_APPLIED_FORCE;
    static const QString COL_APPLIED_FORCE_ID;
    static const QString COL_APPLIED_FORCE_ORGAN;
    static const QString COL_APPLIED_FORCE_DIRECTION;
    static const QString COL_APPLIED_FORCE_INTENSITY;
    static const QHash<QString, QVariant::Type> HASH_APPLIED_FORCE_TYPES;

    //Transportation
    static const QString TBL_TRANSPORTATION;
    static const QString COL_TRANSPORTATION_ID;
    static const QString COL_TRANSPORTATION_NAME;
    static const QString COL_TRANSPORTATION_FIXED_ROLLER;
    static const QString COL_TRANSPORTATION_BRAKES;
    static const QString COL_TRANSPORTATION_EMPTY_WEIGHT;
    static const QString COL_TRANSPORTATION_MAX_LOAD;
    static const QHash<QString, QVariant::Type> HASH_TRANSPORTATION_TYPES;

    //Type_of_Grasping
    static const QString TBL_TYPE_OF_GRASPING;
    static const QString COL_TYPE_OF_GRASPING_ID;
    static const QString COL_TYPE_OF_GRASPING_NAME;
    static const QHash<QString, QVariant::Type> HASH_TYPE_OF_GRASPING_TYPES;

    //Equipment
    static const QString TBL_EQUIPMENT;
    static const QString COL_EQUIPMENT_ID;
    static const QString COL_EQUIPMENT_NAME;
    static const QString COL_EQUIPMENT_RECOIL_COUNT;
    static const QString COL_EQUIPMENT_RECOIL_INTENSITY;
    static const QString COL_EQUIPMENT_VIBRATION_COUNT;
    static const QString COL_EQUIPMENT_VIBRATION_INTENSITY;
    static const QHash<QString, QVariant::Type> HASH_EQUIPMENT_TYPES;

    //Work_Condition
    static const QString TBL_WORK_CONDITION;
    static const QString COL_WORK_CONDITION_ID;
    static const QString COL_WORK_CONDITION_PRECISION;
    static const QString COL_WORK_CONDITION_VELOCITY;
    static const QString COL_WORK_CONDITION_ACCELERATION;
    static const QString COL_WORK_CONDITION_GRIP_CONDITION;
    static const QString COL_WORK_CONDITION_ACCESSIBILITY;
    static const QString COL_WORK_CONDITION_GROUND;
    static const QString COL_WORK_CONDITION_LIGHTING;
    static const QString COL_WORK_CONDITION_CLIMATE;
    static const QString COL_WORK_CONDITION_WIND;
    static const QString COL_WORK_CONDITION_CLOTHING;
    static const QString COL_WORK_CONDITION_VIBRATION;
    static const QString COL_WORK_CONDITION_ROOM_TO_MOVE;
    static const QString COL_WORK_CONDITION_HEAD_SUPPORTED;
    static const QString COL_WORK_CONDITION_RIGHT_UPPER_ARM_SUPPORTED;
    static const QString COL_WORK_CONDITION_LEFT_UPPER_ARM_SUPPORTED;
    static const QString COL_WORK_CONDITION_RIGHT_FOREARM_SUPPORTED;
    static const QString COL_WORK_CONDITION_LEFT_FOREARM_SUPPORTED;
    static const QString COL_WORK_CONDITION_RIGHT_HAND_SUPPORTED;
    static const QString COL_WORK_CONDITION_LEFT_HAND_SUPPORTED;
    static const QString COL_WORK_CONDITION_TRUNK_SUPPORT;
    static const QString COL_WORK_CONDITION_RIGHT_THIGH_SUPPORTED;
    static const QString COL_WORK_CONDITION_LEFT_THIGH_SUPPORTED;
    static const QString COL_WORK_CONDITION_RIGHT_LOWER_LEG_SUPPORTED;
    static const QString COL_WORK_CONDITION_LEFT_LOWER_LEG_SUPPORTED;
    static const QHash<QString, QVariant::Type> HASH_WORK_CONDITION_TYPES;

    //Connection
    static const QString TBL_CONNECTION;
    static const QString COL_CONNECTION_ID;
    static const QString COL_CONNECTION_NAME;
    static const QString COL_CONNECTION_USERNAME;
    static const QString COL_CONNECTION_PASSWORD;
    static const QString COL_CONNECTION_SERVER_ADDRESS;
    static const QString COL_CONNECTION_PORT;
    static const QString COL_CONNECTION_DEFAULT;
    static const QString COL_CONNECTION_ANALYST_ID;
    static const QHash<QString, QVariant::Type> HASH_CONNECTION_TYPES;

    //Shift
    static const QString TBL_SHIFT;
    static const QString COL_SHIFT_ID;
    static const QString COL_SHIFT_RECORDING_ID;
    static const QString COL_SHIFT_TYPE;
    static const QString COL_SHIFT_START;
    static const QString COL_SHIFT_END;
    static const QString COL_SHIFT_ROTATION_GROUP_ID;
    static const QHash<QString, QVariant::Type> HASH_SHIFT_TYPES;

    //Employee_works_Shift
    static const QString TBL_EMPLOYEE_WORKS_SHIFT;
    static const QString COL_EMPLOYEE_WORKS_SHIFT_EMPLOYEE_ID;
    static const QString COL_EMPLOYEE_WORKS_SHIFT_SHIFT_ID;
    static const QHash<QString, QVariant::Type> HASH_EMPLOYEE_WORKS_SHIFT_TYPES;

    //Break
    static const QString TBL_BREAK;
    static const QString COL_BREAK_ID;
    static const QString COL_BREAK_DURATION;
    static const QHash<QString, QVariant::Type> HASH_BREAK_TYPES;

    // Rotation Group
    static const QString TBL_ROTATION_GROUP;
    static const QString COL_ROTATION_GROUP_ID;
    static const QString COL_ROTATION_GROUP_ORDER_NUMBER;
    static const QString COL_ROTATION_GROUP_IS_TASK;
    static const QString COL_ROTATION_GROUP_ENTRY_ID;
    static const QHash<QString, QVariant::Type> HASH_ROTATION_GROUP_TYPES;

    // Rotation Group Task
    static const QString TBL_ROTATION_GROUP_TASK;
    static const QString COL_ROTATION_GROUP_TASK_ID;
    static const QString COL_ROTATION_GROUP_TASK_NAME;
    static const QString COL_ROTATION_GROUP_TASK_DURATION;
    static const QHash<QString, QVariant::Type> HASH_ROTATION_GROUP_TASK_TYPES;

    // Rotation Group Task Entry
    static const QString TBL_ROTATION_GROUP_TASK_ENTRY;
    static const QString COL_ROTATION_GROUP_TASK_ENTRY_ID;
    static const QString COL_ROTATION_GROUP_TASK_ENTRY_TASK_ID;
    static const QString COL_ROTATION_GROUP_TASK_ENTRY_WORKPLACE_ID;
    static const QString COL_ROTATION_GROUP_TASK_ENTRY_DURATION;
    static const QHash<QString, QVariant::Type> HASH_ROTATION_GROUP_TASK_ENTRY_TYPES;

    //Table list
    static const QList<QString> LIST_TABLE_NAMES;
};

#endif // DBCONSTANTS_H
