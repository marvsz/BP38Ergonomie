#include "dbconstants.h"
#include "qhashbuilder.h"


//Analyst
const QString DBConstants::TBL_ANALYST = "Analyst";
const QString DBConstants::COL_ANALYST_ID = "analyst_ID";
const QString DBConstants::COL_ANALYST_LASTNAME = "analyst_last_name";
const QString DBConstants::COL_ANALYST_FIRSTNAME = "analyst_first_name";
const QString DBConstants::COL_ANALYST_EXPERIENCE = "analyst_experience";
const QString DBConstants::COL_ANALYST_EMPLOYER_ID = "employer_ID";
const QHash<QString, QVariant::Type> DBConstants::HASH_ANALYST_TYPES = QHashBuilder<QString, QVariant::Type>().add(DBConstants::COL_ANALYST_ID, QVariant::Int).add(DBConstants::COL_ANALYST_LASTNAME, QVariant::Int).add(DBConstants::COL_ANALYST_FIRSTNAME, QVariant::Int).add(DBConstants::COL_ANALYST_EXPERIENCE, QVariant::Int).add(DBConstants::COL_ANALYST_EMPLOYER_ID, QVariant::Int).build();

//Employer
const QString DBConstants::TBL_EMPLOYER = "Employer";
const QString DBConstants::COL_EMPLOYER_ID = "employer_ID";
const QString DBConstants::COL_EMPLOYER_NAME = "employer_name";
const QHash<QString, QVariant::Type> DBConstants::HASH_EMPLOYER_TYPES = QHashBuilder<QString, QVariant::Type>().add(DBConstants::COL_EMPLOYER_ID, QVariant::Int).add(DBConstants::COL_EMPLOYER_NAME, QVariant::Int).build();

//Corporation
const QString DBConstants::TBL_CORPORATION = "Corporation";
const QString DBConstants::COL_CORPORATION_ID = "corporation_ID";
const QString DBConstants::COL_CORPORATION_NAME = "corporation_name";
const QString DBConstants::COL_CORPORATION_BRANCH_OF_INDUSTRY_ID = "branch_of_industry_ID";
const QHash<QString, QVariant::Type> DBConstants::HASH_CORPORATION_TYPES = QHashBuilder<QString, QVariant::Type>().add(DBConstants::COL_CORPORATION_ID, QVariant::Int).add(DBConstants::COL_CORPORATION_NAME, QVariant::Int).add(DBConstants::COL_CORPORATION_BRANCH_OF_INDUSTRY_ID, QVariant::Int).build();

//Branch of Industry
const QString DBConstants::TBL_BRANCH_OF_INDUSTRY = "Branch_of_Industry";
const QString DBConstants::COL_BRANCH_OF_INDUSTRY_ID = "branch_of_industry_ID";
const QString DBConstants::COL_BRANCH_OF_INDUSTRY_NAME = "name";
const QString DBConstants::COL_BRANCH_OF_INDUSTRY_DESCRIPTION = "description";
const QHash<QString, QVariant::Type> DBConstants::HASH_BRANCH_OF_INDUSTRY_TYPES = QHashBuilder<QString, QVariant::Type>().add(DBConstants::COL_BRANCH_OF_INDUSTRY_ID, QVariant::Int).add(DBConstants::COL_BRANCH_OF_INDUSTRY_NAME, QVariant::String).add(DBConstants::COL_BRANCH_OF_INDUSTRY_DESCRIPTION, QVariant::String).build();

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
const QHash<QString, QVariant::Type> DBConstants::HASH_FACTORY_TYPES = QHashBuilder<QString, QVariant::Type>().add(DBConstants::COL_FACTORY_ID, QVariant::Int).add(DBConstants::COL_FACTORY_NAME, QVariant::Int).add(DBConstants::COL_FACTORY_STREET, QVariant::Int).add(DBConstants::COL_FACTORY_ZIP, QVariant::Int).add(DBConstants::COL_FACTORY_CITY, QVariant::Int).add(DBConstants::COL_FACTORY_COUNTRY, QVariant::Int).add(DBConstants::COL_FACTORY_CONTACT_PERSON, QVariant::Int).add(DBConstants::COL_FACTORY_HEADCOUNT, QVariant::Int).add(DBConstants::COL_FACTORY_CORPORATION_ID, QVariant::Int).build();

//Recording
const QString DBConstants::TBL_RECORDING = "Recording";
const QString DBConstants::COL_RECORDING_ID = "recording_ID";
const QString DBConstants::COL_RECORDING_START = "recording_start";
const QString DBConstants::COL_RECORDING_END = "recording_end";
const QString DBConstants::COL_RECORDING_FACTORY_ID = "factory_ID";
const QString DBConstants::COL_RECORDING_ANALYST_ID = "analyst_ID";
const QHash<QString, QVariant::Type> DBConstants::HASH_RECORDING_TYPES = QHashBuilder<QString, QVariant::Type>().add(DBConstants::COL_RECORDING_ID, QVariant::Int).add(DBConstants::COL_RECORDING_START, QVariant::Int).add(DBConstants::COL_RECORDING_END, QVariant::Int).add(DBConstants::COL_RECORDING_FACTORY_ID, QVariant::Int).add(DBConstants::COL_RECORDING_ANALYST_ID, QVariant::Int).build();

//Recording observes Line
const QString DBConstants::TBL_RECORDING_OB_LINE = "Recording_observes_Line";
const QString DBConstants::COL_RECORDING_OB_LINE_RECORDING_ID = "recording_ID";
const QString DBConstants::COL_RECORDING_OB_LINE_LINE_ID = "line_ID";
const QHash<QString, QVariant::Type> DBConstants::HASH_RECORDING_OB_LINE_TYPES = QHashBuilder<QString, QVariant::Type>().add(DBConstants::COL_RECORDING_OB_LINE_RECORDING_ID, QVariant::Int).add(DBConstants::COL_RECORDING_OB_LINE_LINE_ID, QVariant::Int).build();

//Recording observes Workplace
const QString DBConstants::TBL_RECORDING_OB_WORKPLACE = "Recording_observes_Workplace";
const QString DBConstants::COL_RECORDING_OB_WORKPLACE_RECORDING_ID = "recording_ID";
const QString DBConstants::COL_RECORDING_OB_WORKPLACE_WORKPLACE_ID = "workplace_ID";
const QHash<QString, QVariant::Type> DBConstants::HASH_RECORDING_OB_WORKPLACE_TYPES = QHashBuilder<QString, QVariant::Type>().add(DBConstants::COL_RECORDING_OB_WORKPLACE_RECORDING_ID, QVariant::Int).add(DBConstants::COL_RECORDING_OB_WORKPLACE_WORKPLACE_ID, QVariant::Int).build();

//Line
const QString DBConstants::TBL_LINE = "Line";
const QString DBConstants::COL_LINE_ID = "line_ID";
const QString DBConstants::COL_LINE_NAME = "line_name";
const QString DBConstants::COL_LINE_DESCRIPTION = "line_description";
const QString DBConstants::COL_LINE_NUMBER_OF_WORKPLACES = "number_of_workplaces";
const QString DBConstants::COL_LINE_FACTORY_ID = "factory_ID";
const QHash<QString, QVariant::Type> DBConstants::HASH_LINE_TYPES = QHashBuilder<QString, QVariant::Type>().add(DBConstants::COL_LINE_ID, QVariant::Int).add(DBConstants::COL_LINE_NAME, QVariant::Int).add(DBConstants::COL_LINE_DESCRIPTION, QVariant::Int).add(DBConstants::COL_LINE_NUMBER_OF_WORKPLACES, QVariant::Int).add(DBConstants::COL_LINE_FACTORY_ID, QVariant::Int).build();

//Workplace
const QString DBConstants::TBL_WORKPLACE = "Workplace";
const QString DBConstants::COL_WORKPLACE_ID = "workplace_ID";
const QString DBConstants::COL_WORKPLACE_NAME = "workplace_name";
const QString DBConstants::COL_WORKPLACE_DESCRIPTION = "workplace_description";
const QString DBConstants::COL_WORKPLACE_PERCENTAGE_WOMAN = "percentage_women";
const QString DBConstants::COL_WORKPLACE_LINE_ID = "line_ID";
const QString DBConstants::COL_WORKPLACE_EMPLOYEE_ID = "employee_ID";
const QString DBConstants::COL_WORKPLACE_CODE = "code";
const QString DBConstants::COL_WORKPLACE_CYCLE_TIME = "cycle_time";
const QString DBConstants::COL_WORKPLACE_SETUP_TIME = "setup_time";
const QString DBConstants::COL_WORKPLACE_BASIC_TIME = "basic_time";
const QString DBConstants::COL_WORKPLACE_REST_TIME = "rest_time";
const QString DBConstants::COL_WORKPLACE_ALLOWANCE_TIME = "allowance_time";
const QHash<QString, QVariant::Type> DBConstants::HASH_WORKPLACE_TYPES = QHashBuilder<QString, QVariant::Type>().add(DBConstants::COL_WORKPLACE_ID, QVariant::Int).add(DBConstants::COL_WORKPLACE_NAME, QVariant::Int).add(DBConstants::COL_WORKPLACE_DESCRIPTION, QVariant::Int).add(DBConstants::COL_WORKPLACE_PERCENTAGE_WOMAN, QVariant::Int).add(DBConstants::COL_WORKPLACE_LINE_ID, QVariant::Int).add(DBConstants::COL_WORKPLACE_CODE, QVariant::Int).add(DBConstants::COL_WORKPLACE_CYCLE_TIME, QVariant::Int).add(DBConstants::COL_WORKPLACE_SETUP_TIME, QVariant::Int).add(DBConstants::COL_WORKPLACE_BASIC_TIME, QVariant::Int).add(DBConstants::COL_WORKPLACE_REST_TIME, QVariant::Int).add(DBConstants::COL_WORKPLACE_ALLOWANCE_TIME, QVariant::Int).add(DBConstants::COL_WORKPLACE_EMPLOYEE_ID, QVariant::Int).build();

//Comment
const QString DBConstants::TBL_COMMENT = "Comment";
const QString DBConstants::COL_COMMENT_ID = "comment_ID";
const QString DBConstants::COL_COMMENT_PROBLEM_NAME = "problem_name";
const QString DBConstants::COL_COMMENT_PROBLEM_DESCRIPTION = "problem_description";
const QString DBConstants::COL_COMMENT_MEASURE_NAME = "measure_name";
const QString DBConstants::COL_COMMENT_MEASURE_DESCRIPTION = "measure_description";
const QString DBConstants::COL_COMMENT_WORKER_PERCEPTION = "worker_perception";
const QString DBConstants::COL_COMMENT_WORKPLACE_ID = "workplace_ID";
const QHash<QString, QVariant::Type> DBConstants::HASH_COMMENT_TYPES = QHashBuilder<QString, QVariant::Type>().add(DBConstants::COL_COMMENT_ID, QVariant::Int).add(DBConstants::COL_COMMENT_PROBLEM_NAME, QVariant::Int).add(DBConstants::COL_COMMENT_PROBLEM_DESCRIPTION, QVariant::Int).add(DBConstants::COL_COMMENT_MEASURE_NAME, QVariant::Int).add(DBConstants::COL_COMMENT_MEASURE_DESCRIPTION, QVariant::Int).add(DBConstants::COL_COMMENT_WORKER_PERCEPTION, QVariant::Int).add(DBConstants::COL_COMMENT_WORKPLACE_ID, QVariant::Int).build();

//Employee
const QString DBConstants::TBL_EMPLOYEE = "Employee";
const QString DBConstants::COL_EMPLOYEE_ID = "employee_ID";
const QString DBConstants::COL_EMPLOYEE_STAFF_NUMBER = "staff_number";
const QString DBConstants::COL_EMPLOYEE_GENDER = "gender";
const QString DBConstants::COL_EMPLOYEE_AGE = "age";
const QString DBConstants::COL_EMPLOYEE_HEIGHT = "height";
const QString DBConstants::COL_EMPLOYEE_NOTE = "note";
const QString DBConstants::COL_EMPLOYEE_BODY_MEASUREMENT_ID = "body_measurement_ID";
const QHash<QString, QVariant::Type> DBConstants::HASH_EMPLOYEE_TYPES = QHashBuilder<QString, QVariant::Type>().add(DBConstants::COL_EMPLOYEE_ID, QVariant::Int).add(DBConstants::COL_EMPLOYEE_STAFF_NUMBER, QVariant::Int).add(DBConstants::COL_EMPLOYEE_AGE, QVariant::Int).add(DBConstants::COL_EMPLOYEE_GENDER, QVariant::Int).add(DBConstants::COL_EMPLOYEE_HEIGHT, QVariant::Int).add(DBConstants::COL_EMPLOYEE_NOTE, QVariant::Int).add(DBConstants::COL_EMPLOYEE_BODY_MEASUREMENT_ID, QVariant::Int).build();

const QString DBConstants::TBL_BODY_MEASUREMENT = "Body_Measurement";
const QString DBConstants::COL_BODY_MEASUREMENT_ID = "body_measurement_ID";
const QString DBConstants::COL_BODY_MEASUREMENT_HEAD_NECK_HEIGHT = "head_neck_height";
const QString DBConstants::COL_BODY_MEASUREMENT_SHOULDER_WIDTH = "shoulder_width";
const QString DBConstants::COL_BODY_MEASUREMENT_SHOULDER_WIDTH_BIACROMIAL = "shoulder_width_biacromial";
const QString DBConstants::COL_BODY_MEASUREMENT_SHOULDER_WIDTH_BIDELTOID = "shoulder_width_bideltoid";
const QString DBConstants::COL_BODY_MEASUREMENT_UPPER_ARM_LENGTH = "upper_arm_length";
const QString DBConstants::COL_BODY_MEASUREMENT_FOREARM_LENGTH = "forearm_length";
const QString DBConstants::COL_BODY_MEASUREMENT_HAND_LENGTH_GRIP_AXIS = "hand_length_grip_axis";
const QString DBConstants::COL_BODY_MEASUREMENT_TORSO_HEIGHT = "torso_height";
const QString DBConstants::COL_BODY_MEASUREMENT_THIGH_LENGTH = "thigh_length";
const QString DBConstants::COL_BODY_MEASUREMENT_TIBIAL_HEIGHT = "tibial_height";
const QString DBConstants::COL_BODY_MEASUREMENT_FOOT_LENGTH = "foot_length";
const QHash<QString, QVariant::Type> DBConstants::HASH_BODY_MEASUREMENT_TYPES = QHashBuilder<QString, QVariant::Type>().add(DBConstants::COL_BODY_MEASUREMENT_ID, QVariant::Int).add(DBConstants::COL_BODY_MEASUREMENT_HEAD_NECK_HEIGHT, QVariant::Int).add(DBConstants::COL_BODY_MEASUREMENT_SHOULDER_WIDTH, QVariant::Int).add(DBConstants::COL_BODY_MEASUREMENT_SHOULDER_WIDTH_BIACROMIAL, QVariant::Int).add(DBConstants::COL_BODY_MEASUREMENT_SHOULDER_WIDTH_BIDELTOID, QVariant::Int).add(DBConstants::COL_BODY_MEASUREMENT_UPPER_ARM_LENGTH, QVariant::Int).add(DBConstants::COL_BODY_MEASUREMENT_FOREARM_LENGTH, QVariant::Int).add(DBConstants::COL_BODY_MEASUREMENT_HAND_LENGTH_GRIP_AXIS, QVariant::Int).add(DBConstants::COL_BODY_MEASUREMENT_TORSO_HEIGHT, QVariant::Int).add(DBConstants::COL_BODY_MEASUREMENT_THIGH_LENGTH, QVariant::Int).add(DBConstants::COL_BODY_MEASUREMENT_TIBIAL_HEIGHT, QVariant::Int).add(DBConstants::COL_BODY_MEASUREMENT_FOOT_LENGTH, QVariant::Int).build();


//Employee_works_Shift
const QString DBConstants::TBL_EMPLOYEE_WORKS_SHIFT = "Employee_works_Shift";
const QString DBConstants::COL_EMPLOYEE_WORKS_SHIFT_EMPLOYEE_ID = "employee_ID";
const QString DBConstants::COL_EMPLOYEE_WORKS_SHIFT_SHIFT_ID = "shift_ID";
const QHash<QString, QVariant::Type> DBConstants::HASH_EMPLOYEE_WORKS_SHIFT_TYPES = QHashBuilder<QString, QVariant::Type>().add(DBConstants::COL_EMPLOYEE_WORKS_SHIFT_EMPLOYEE_ID, QVariant::Int).add(DBConstants::COL_EMPLOYEE_WORKS_SHIFT_SHIFT_ID, QVariant::Int).build();

//Product
const QString DBConstants::TBL_PRODUCT = "Product";
const QString DBConstants::COL_PRODUCT_ID = "product_ID";
const QString DBConstants::COL_PRODUCT_NUMBER = "product_number";
const QString DBConstants::COL_PRODUCT_NAME = "product_name";
const QString DBConstants::COL_PRODUCT_TOTAL_PERCENTAGE = "total_percentage";
const QHash<QString, QVariant::Type> DBConstants::HASH_PRODUCT_TYPES = QHashBuilder<QString, QVariant::Type>().add(DBConstants::COL_PRODUCT_ID, QVariant::Int).add(DBConstants::COL_PRODUCT_NUMBER, QVariant::Int).add(DBConstants::COL_PRODUCT_NAME, QVariant::Int).add(DBConstants::COL_PRODUCT_TOTAL_PERCENTAGE, QVariant::Int).build();

//Shift
const QString DBConstants::TBL_SHIFT = "Shift";
const QString DBConstants::COL_SHIFT_ID = "shift_ID";
const QString DBConstants::COL_SHIFT_ROTATION_SHIFT_ID = "rotation_shift_ID";
const QString DBConstants::COL_SHIFT_TYPE = "type";
const QString DBConstants::COL_SHIFT_START = "start";
const QString DBConstants::COL_SHIFT_END = "end";
const QHash<QString, QVariant::Type> DBConstants::HASH_SHIFT_TYPES = QHashBuilder<QString, QVariant::Type>().add(DBConstants::COL_SHIFT_ID, QVariant::Int).add(DBConstants::COL_SHIFT_ROTATION_SHIFT_ID, QVariant::Int).add(DBConstants::COL_SHIFT_TYPE, QVariant::Int).add(DBConstants::COL_SHIFT_START, QVariant::Int).add(DBConstants::COL_SHIFT_END, QVariant::Int).build();

//Break
const QString DBConstants::TBL_BREAK = "Break";
const QString DBConstants::COL_BREAK_ID = "break_ID";
const QHash<QString, QVariant::Type> DBConstants::HASH_BREAK_TYPES = QHashBuilder<QString, QVariant::Type>().add(DBConstants::COL_BREAK_ID, QVariant::Int).build();

//Activity
const QString DBConstants::TBL_ACTIVITY = "Activity";
const QString DBConstants::COL_ACTIVITY_ID = "activity_ID";
const QString DBConstants::COL_ACTIVITY_DESCRIPTION = "activity_description";
const QString DBConstants::COL_ACTIVITY_REPETITIONS = "activity_repetitions";
const QString DBConstants::COL_ACTIVITY_PRODUCT_ID = "product_ID";
const QString DBConstants::COL_ACTIVITY_WORKPLACE_ID = "workplace_ID";
const QHash<QString, QVariant::Type> DBConstants::HASH_ACTIVITY_TYPES = QHashBuilder<QString, QVariant::Type>().add(DBConstants::COL_ACTIVITY_ID, QVariant::Int).add(DBConstants::COL_ACTIVITY_DESCRIPTION, QVariant::String).add(DBConstants::COL_ACTIVITY_REPETITIONS, QVariant::Int).add(DBConstants::COL_ACTIVITY_PRODUCT_ID, QVariant::Int).add(DBConstants::COL_ACTIVITY_WORKPLACE_ID, QVariant::Int).build();

//Body_Posture
const QString DBConstants::TBL_BODY_POSTURE = "Body_Posture";
const QString DBConstants::COL_BODY_POSTURE_ID = "posture_ID";
const QString DBConstants::COL_BODY_POSTURE_HEAD_TILT = "head_tilt";
const QString DBConstants::COL_BODY_POSTURE_HEAD_TILT_SIDEWAYS = "head_tilt_sideways";
const QString DBConstants::COL_BODY_POSTURE_HEAD_TWIST = "head_twist";
const QString DBConstants::COL_BODY_POSTURE_ARM_OPENING_ANGLE_RIGHT = "arm_opening_angle_right";
const QString DBConstants::COL_BODY_POSTURE_ARM_OPENING_ANGLE_LEFT = "arm_opening_angle_left";
const QString DBConstants::COL_BODY_POSTURE_UPPER_ARM_ANGLE_RIGHT = "upper_arm_angle_right";
const QString DBConstants::COL_BODY_POSTURE_UPPER_ARM_ANGLE_LEFT = "upper_arm_angle_left";
const QString DBConstants::COL_BODY_POSTURE_UPPER_ARM_TWIST_RIGHT = "upper_arm_twist_right";
const QString DBConstants::COL_BODY_POSTURE_UPPER_ARM_TWIST_LEFT = "upper_arm_twist_left";
const QString DBConstants::COL_BODY_POSTURE_FOREARM_ANGLE_RIGHT = "forearm_angle_right";
const QString DBConstants::COL_BODY_POSTURE_FOREARM_ANGLE_LEFT = "forearm_angle_left";
const QString DBConstants::COL_BODY_POSTURE_FOREARM_TWIST_RIGHT = "forearm_twist_right";
const QString DBConstants::COL_BODY_POSTURE_FOREARM_TWIST_LEFT = "forearm_twist_left";
const QString DBConstants::COL_BODY_POSTURE_WRIST_ANGLE_RIGHT = "wrist_angle_right";
const QString DBConstants::COL_BODY_POSTURE_WRIST_ANGLE_SIDEWAYS_RIGHT = "wrist_angle_sideways_right";
const QString DBConstants::COL_BODY_POSTURE_WRIST_ANGLE_LEFT = "wrist_angle_left";
const QString DBConstants::COL_BODY_POSTURE_WRIST_ANGLE_SIDEWAYS_LEFT = "wrist_angle_sideways_left";
const QString DBConstants::COL_BODY_POSTURE_WRIST_MOVEMENT_RIGHT = "wrist_movement_right";
const QString DBConstants::COL_BODY_POSTURE_WRIST_MOVEMENT_LEFT = "wrist_movement_left";
const QString DBConstants::COL_BODY_POSTURE_TRUNK_TILT = "trunk_tilt";
const QString DBConstants::COL_BODY_POSTURE_TRUNK_TILT_SIDEWAYS = "trunk_tilt_sideways";
const QString DBConstants::COL_BODY_POSTURE_TRUNK_TWIST = "trunk_twist";
const QString DBConstants::COL_BODY_POSTURE_LEG_COUNT = "leg_count";
const QString DBConstants::COL_BODY_POSTURE_LEG_POSTURE = "leg_posture";
const QString DBConstants::COL_BODY_POSTURE_HIP_ANGLE_RIGHT = "hip_angle_right";
const QString DBConstants::COL_BODY_POSTURE_HIP_ANGLE_LEFT = "hip_angle_left";
const QString DBConstants::COL_BODY_POSTURE_HIP_ANGLE_SIDEWAYS_LEFT = "hip_angle_sideways_left";
const QString DBConstants::COL_BODY_POSTURE_HIP_ANGLE_SIDEWAYS_RIGHT = "hip_angle_sideways_right";
const QString DBConstants::COL_BODY_POSTURE_HIP_TWIST_LEFT = "hip_twist_left";
const QString DBConstants::COL_BODY_POSTURE_HIP_TWIST_RIGHT = "hip_twist_right";
const QString DBConstants::COL_BODY_POSTURE_KNEE_ANGLE_RIGHT = "knee_angle_right";
const QString DBConstants::COL_BODY_POSTURE_KNEE_ANGLE_LEFT = "knee_angle_left";
const QString DBConstants::COL_BODY_POSTURE_ANKLE_ANGLE_RIGHT = "ankle_angle_right";
const QString DBConstants::COL_BODY_POSTURE_ANKLE_ANGLE_SIDEWAYS_RIGHT = "ankle_angle_sideways_right";
const QString DBConstants::COL_BODY_POSTURE_ANKLE_ANGLE_LEFT = "ankle_angle_left";
const QString DBConstants::COL_BODY_POSTURE_ANKLE_ANGLE_SIDEWAYS_LEFT = "ankle_angle_sideways_left";
const QHash<QString, QVariant::Type> DBConstants::HASH_BODY_POSTURE_TYPES = QHashBuilder<QString, QVariant::Type>().add(DBConstants::COL_BODY_POSTURE_ID, QVariant::Int).add(DBConstants::COL_BODY_POSTURE_HEAD_TILT, QVariant::Int).add(DBConstants::COL_BODY_POSTURE_HEAD_TILT_SIDEWAYS, QVariant::Int).add(DBConstants::COL_BODY_POSTURE_HEAD_TWIST, QVariant::Int).add(DBConstants::COL_BODY_POSTURE_ARM_OPENING_ANGLE_RIGHT, QVariant::Int).add(DBConstants::COL_BODY_POSTURE_ARM_OPENING_ANGLE_LEFT, QVariant::Int).add(DBConstants::COL_BODY_POSTURE_UPPER_ARM_ANGLE_RIGHT, QVariant::Int).add(DBConstants::COL_BODY_POSTURE_UPPER_ARM_ANGLE_LEFT, QVariant::Int).add(DBConstants::COL_BODY_POSTURE_UPPER_ARM_TWIST_RIGHT, QVariant::Int).add(DBConstants::COL_BODY_POSTURE_UPPER_ARM_TWIST_LEFT, QVariant::Int).add(DBConstants::COL_BODY_POSTURE_FOREARM_ANGLE_RIGHT, QVariant::Int).add(DBConstants::COL_BODY_POSTURE_FOREARM_ANGLE_LEFT, QVariant::Int).add(DBConstants::COL_BODY_POSTURE_FOREARM_TWIST_RIGHT, QVariant::Int).add(DBConstants::COL_BODY_POSTURE_FOREARM_TWIST_LEFT, QVariant::Int).add(DBConstants::COL_BODY_POSTURE_WRIST_ANGLE_RIGHT, QVariant::Int).add(DBConstants::COL_BODY_POSTURE_WRIST_ANGLE_SIDEWAYS_RIGHT, QVariant::Int).add(DBConstants::COL_BODY_POSTURE_WRIST_ANGLE_LEFT, QVariant::Int).add(DBConstants::COL_BODY_POSTURE_WRIST_ANGLE_SIDEWAYS_LEFT, QVariant::Int).add(DBConstants::COL_BODY_POSTURE_WRIST_MOVEMENT_RIGHT, QVariant::Int).add(DBConstants::COL_BODY_POSTURE_WRIST_MOVEMENT_LEFT, QVariant::Int).add(DBConstants::COL_BODY_POSTURE_TRUNK_TILT, QVariant::Int).add(DBConstants::COL_BODY_POSTURE_TRUNK_TILT_SIDEWAYS, QVariant::Int).add(DBConstants::COL_BODY_POSTURE_TRUNK_TWIST, QVariant::Int).add(DBConstants::COL_BODY_POSTURE_LEG_COUNT, QVariant::Int).add(DBConstants::COL_BODY_POSTURE_LEG_POSTURE, QVariant::String).add(DBConstants::COL_BODY_POSTURE_HIP_ANGLE_RIGHT, QVariant::Int).add(DBConstants::COL_BODY_POSTURE_HIP_ANGLE_LEFT, QVariant::Int).add(DBConstants::COL_BODY_POSTURE_HIP_ANGLE_SIDEWAYS_LEFT, QVariant::Int).add(DBConstants::COL_BODY_POSTURE_HIP_ANGLE_SIDEWAYS_RIGHT, QVariant::Int).add(DBConstants::COL_BODY_POSTURE_HIP_TWIST_LEFT, QVariant::Int).add(DBConstants::COL_BODY_POSTURE_HIP_TWIST_RIGHT, QVariant::Int).add(DBConstants::COL_BODY_POSTURE_KNEE_ANGLE_RIGHT, QVariant::Int).add(DBConstants::COL_BODY_POSTURE_KNEE_ANGLE_LEFT, QVariant::Int).add(DBConstants::COL_BODY_POSTURE_ANKLE_ANGLE_RIGHT, QVariant::Int).add(DBConstants::COL_BODY_POSTURE_ANKLE_ANGLE_SIDEWAYS_RIGHT, QVariant::Int).add(DBConstants::COL_BODY_POSTURE_ANKLE_ANGLE_LEFT, QVariant::Int).add(DBConstants::COL_BODY_POSTURE_ANKLE_ANGLE_SIDEWAYS_LEFT, QVariant::Int).build();

//Workprocess
const QString DBConstants::TBL_WORK_PROCESS = "Work_Process";
const QString DBConstants::COL_WORK_PROCESS_ACTIVITY_ID = "activity_ID";
const QString DBConstants::COL_WORK_PROCESS_ID = "process_ID";
const QString DBConstants::COL_WORK_PROCESS_TYPE = "type";
const QString DBConstants::COL_WORK_PROCESS_DESCRIPTION = "process_description";
const QString DBConstants::COL_WORK_PROCESS_BEGIN = "begin";
const QString DBConstants::COL_WORK_PROCESS_END = "end";
const QString DBConstants::COL_WORK_PROCESS_MTM_CODE = "mtm_code";
const QString DBConstants::COL_WORK_PROCESS_FREQUENCY = "frequency";
const QString DBConstants::COL_WORK_PROCESS_IMPULSE_INTENSITY = "impulse_intensity";
const QString DBConstants::COL_WORK_PROCESS_IMPULSE_COUNT = "impulse_count";
const QString DBConstants::COL_WORK_PROCESS_WORKING_HEIGHT = "working_height";
const QString DBConstants::COL_WORK_PROCESS_DISTANCE = "distance";
const QString DBConstants::COL_WORK_PROCESS_POSTURE_ID = "posture_ID";
const QString DBConstants::COL_WORK_PROCESS_EQUIPMENT_ID = "equipment_ID";
const QString DBConstants::COL_WORK_PROCESS_CONDITION_ID = "condition_ID";
const QString DBConstants::COL_WORK_PROCESS_APPLIED_FORCE_ID = "applied_force_ID";
const QString DBConstants::COL_WORK_PROCESS_LOAD_HANDLING_ID = "load_handling_ID";
const QHash<QString, QVariant::Type> DBConstants::HASH_WORK_PROCESS_TYPES = QHashBuilder<QString, QVariant::Type>().add(DBConstants::COL_WORK_PROCESS_ACTIVITY_ID, QVariant::Int).add(DBConstants::COL_WORK_PROCESS_TYPE, QVariant::Int).add(DBConstants::COL_WORK_PROCESS_ID, QVariant::Int).add(DBConstants::COL_WORK_PROCESS_DESCRIPTION, QVariant::String).add(DBConstants::COL_WORK_PROCESS_BEGIN, QVariant::String).add(DBConstants::COL_WORK_PROCESS_END, QVariant::String).add(DBConstants::COL_WORK_PROCESS_MTM_CODE, QVariant::String).add(DBConstants::COL_WORK_PROCESS_FREQUENCY, QVariant::Int).add(DBConstants::COL_WORK_PROCESS_IMPULSE_INTENSITY, QVariant::Int).add(DBConstants::COL_WORK_PROCESS_IMPULSE_COUNT, QVariant::Int).add(DBConstants::COL_WORK_PROCESS_WORKING_HEIGHT, QVariant::Int).add(DBConstants::COL_WORK_PROCESS_DISTANCE, QVariant::Int).add(DBConstants::COL_WORK_PROCESS_POSTURE_ID, QVariant::Int).add(DBConstants::COL_WORK_PROCESS_EQUIPMENT_ID, QVariant::Int).add(DBConstants::COL_WORK_PROCESS_CONDITION_ID, QVariant::Int).add(DBConstants::COL_WORK_PROCESS_APPLIED_FORCE_ID, QVariant::Int).add(DBConstants::COL_WORK_PROCESS_LOAD_HANDLING_ID, QVariant::Int).build();

//Load_Handling_Type
const QString DBConstants::TBL_LOAD_HANDLING_TYPE = "Load_Handling_Type";
const QString DBConstants::COL_LOAD_HANDLING_TYPE_ID = "load_handling_type_ID";
const QString DBConstants::COL_LOAD_HANDLING_TYPE_NAME = "load_handling_type_name";
const QHash<QString, QVariant::Type> DBConstants::HASH_LOAD_HANDLING_TYPE_TYPES = QHashBuilder<QString, QVariant::Type>().add(DBConstants::COL_LOAD_HANDLING_TYPE_ID, QVariant::Int).add(DBConstants::COL_LOAD_HANDLING_TYPE_NAME, QVariant::String).build();

//Load_Handling
const QString DBConstants::TBL_LOAD_HANDLING = "Load_Handling";
const QString DBConstants::COL_LOAD_HANDLING_ID = "load_handling_ID";
const QString DBConstants::COL_LOAD_HANDLING_LOAD = "load";
const QString DBConstants::COL_LOAD_HANDLING_DISTANCE = "distance";
const QString DBConstants::COL_LOAD_HANDLING_LOAD_HANDLING_TYPE_ID = "load_handling_type_ID";
const QString DBConstants::COL_LOAD_HANDLING_TYPE_OF_GRASPING = "type_of_grasping_ID";
const QString DBConstants::COL_LOAD_HANDLING_TRANSPORTATION_ID = "transportation_ID";
const QHash<QString, QVariant::Type> DBConstants::HASH_LOAD_HANDLING_TYPES = QHashBuilder<QString, QVariant::Type>().add(DBConstants::COL_LOAD_HANDLING_ID, QVariant::Int).add(DBConstants::COL_LOAD_HANDLING_LOAD, QVariant::Int).add(DBConstants::COL_LOAD_HANDLING_DISTANCE, QVariant::Int).add(DBConstants::COL_LOAD_HANDLING_LOAD_HANDLING_TYPE_ID, QVariant::Int).add(DBConstants::COL_LOAD_HANDLING_TYPE_OF_GRASPING, QVariant::Int).add(DBConstants::COL_LOAD_HANDLING_TRANSPORTATION_ID, QVariant::Int).build();

//Applied_Force
const QString DBConstants::TBL_APPLIED_FORCE = "Applied_Force";
const QString DBConstants::COL_APPLIED_FORCE_ID = "applied_force_ID";
const QString DBConstants::COL_APPLIED_FORCE_ORGAN = "organ";
const QString DBConstants::COL_APPLIED_FORCE_DIRECTION = "direction";
const QString DBConstants::COL_APPLIED_FORCE_INTENSITY = "intensity";
const QHash<QString, QVariant::Type> DBConstants::HASH_APPLIED_FORCE_TYPES = QHashBuilder<QString, QVariant::Type>().add(DBConstants::COL_APPLIED_FORCE_ID, QVariant::Int).add(DBConstants::COL_APPLIED_FORCE_ORGAN, QVariant::String).add(DBConstants::COL_APPLIED_FORCE_DIRECTION, QVariant::String).add(DBConstants::COL_APPLIED_FORCE_INTENSITY, QVariant::Int).build();

//Transportation
const QString DBConstants::TBL_TRANSPORTATION = "Transportation";
const QString DBConstants::COL_TRANSPORTATION_ID = "transportation_ID";
const QString DBConstants::COL_TRANSPORTATION_NAME = "transportation_name";
const QString DBConstants::COL_TRANSPORTATION_FIXED_ROLLER = "fixed_roller";
const QString DBConstants::COL_TRANSPORTATION_BRAKES = "brakes";
const QString DBConstants::COL_TRANSPORTATION_EMPTY_WEIGHT = "empty_weight";
const QString DBConstants::COL_TRANSPORTATION_MAX_LOAD = "max_load";
const QHash<QString, QVariant::Type> DBConstants::HASH_TRANSPORTATION_TYPES = QHashBuilder<QString, QVariant::Type>().add(DBConstants::COL_TRANSPORTATION_ID, QVariant::Int).add(DBConstants::COL_TRANSPORTATION_NAME, QVariant::String).add(DBConstants::COL_TRANSPORTATION_FIXED_ROLLER, QVariant::Int).add(DBConstants::COL_TRANSPORTATION_BRAKES, QVariant::Int).add(DBConstants::COL_TRANSPORTATION_EMPTY_WEIGHT, QVariant::Int).add(DBConstants::COL_TRANSPORTATION_MAX_LOAD, QVariant::Int).build();

//Type_of_Grasping
const QString DBConstants::TBL_TYPE_OF_GRASPING = "Type_of_Grasping";
const QString DBConstants::COL_TYPE_OF_GRASPING_ID = "type_of_grasping_ID";
const QString DBConstants::COL_TYPE_OF_GRASPING_NAME = "type_of_grasping_name";
const QHash<QString, QVariant::Type> DBConstants::HASH_TYPE_OF_GRASPING_TYPES = QHashBuilder<QString, QVariant::Type>().add(DBConstants::COL_TYPE_OF_GRASPING_ID, QVariant::Int).add(DBConstants::COL_TYPE_OF_GRASPING_NAME, QVariant::String).build();

//Equipment
const QString DBConstants::TBL_EQUIPMENT = "Equipment";
const QString DBConstants::COL_EQUIPMENT_ID = "equipment_ID";
const QString DBConstants::COL_EQUIPMENT_NAME = "equipment_name";
const QString DBConstants::COL_EQUIPMENT_RECOIL_COUNT = "recoil_count";
const QString DBConstants::COL_EQUIPMENT_RECOIL_INTENSITY = "recoil_intensity";
const QString DBConstants::COL_EQUIPMENT_VIBRATION_COUNT = "vibration_count";
const QString DBConstants::COL_EQUIPMENT_VIBRATION_INTENSITY = "vibration_intensity";
const QHash<QString, QVariant::Type> DBConstants::HASH_EQUIPMENT_TYPES = QHashBuilder<QString, QVariant::Type>().add(DBConstants::COL_EQUIPMENT_ID, QVariant::Int).add(DBConstants::COL_EQUIPMENT_NAME, QVariant::String).add(DBConstants::COL_EQUIPMENT_RECOIL_COUNT, QVariant::Int).add(DBConstants::COL_EQUIPMENT_RECOIL_INTENSITY, QVariant::Int).add(DBConstants::COL_EQUIPMENT_VIBRATION_COUNT, QVariant::Int).add(DBConstants::COL_EQUIPMENT_VIBRATION_INTENSITY, QVariant::Int).build();

//Work_Condition
const QString DBConstants::TBL_WORK_CONDITION = "Work_Condition";
const QString DBConstants::COL_WORK_CONDITION_ID = "condition_ID";
const QString DBConstants::COL_WORK_CONDITION_PRECISION = "precision";
const QString DBConstants::COL_WORK_CONDITION_VELOCITY = "velocity";
const QString DBConstants::COL_WORK_CONDITION_ACCELERATION = "acceleration";
const QString DBConstants::COL_WORK_CONDITION_GRIP_CONDITION = "grip_condition";
const QString DBConstants::COL_WORK_CONDITION_ACCESSIBILITY = "accessibility";
const QString DBConstants::COL_WORK_CONDITION_GROUND = "ground";
const QString DBConstants::COL_WORK_CONDITION_LIGHTING = "lighting";
const QString DBConstants::COL_WORK_CONDITION_CLIMATE = "climate";
const QString DBConstants::COL_WORK_CONDITION_WIND = "wind";
const QString DBConstants::COL_WORK_CONDITION_CLOTHING = "clothing";
const QString DBConstants::COL_WORK_CONDITION_VIBRATION = "vibration";
const QString DBConstants::COL_WORK_CONDITION_ROOM_TO_MOVE = "room_to_move";
const QString DBConstants::COL_WORK_CONDITION_HEAD_SUPPORTED = "head_supported";
const QString DBConstants::COL_WORK_CONDITION_RIGHT_UPPER_ARM_SUPPORTED = "right_upper_arm_supported";
const QString DBConstants::COL_WORK_CONDITION_LEFT_UPPER_ARM_SUPPORTED = "left_upper_arm_supported";
const QString DBConstants::COL_WORK_CONDITION_RIGHT_FOREARM_SUPPORTED = "right_forearm_supported";
const QString DBConstants::COL_WORK_CONDITION_LEFT_FOREARM_SUPPORTED = "left_forearm_supported";
const QString DBConstants::COL_WORK_CONDITION_RIGHT_HAND_SUPPORTED = "right_hand_supported";
const QString DBConstants::COL_WORK_CONDITION_LEFT_HAND_SUPPORTED = "left_hand_supported";
const QString DBConstants::COL_WORK_CONDITION_TRUNK_SUPPORT = "trunk_support";
const QString DBConstants::COL_WORK_CONDITION_RIGHT_THIGH_SUPPORTED = "right_thigh_supported";
const QString DBConstants::COL_WORK_CONDITION_LEFT_THIGH_SUPPORTED = "left_thigh_supported";
const QString DBConstants::COL_WORK_CONDITION_RIGHT_LOWER_LEG_SUPPORTED = "right_lower_leg_supported";
const QString DBConstants::COL_WORK_CONDITION_LEFT_LOWER_LEG_SUPPORTED = "left_lower_leg_supported";
const QHash<QString, QVariant::Type> DBConstants::HASH_WORK_CONDITION_TYPES = QHashBuilder<QString, QVariant::Type>().add(DBConstants::COL_WORK_CONDITION_ID, QVariant::Int).add(DBConstants::COL_WORK_CONDITION_PRECISION, QVariant::Int).add(DBConstants::COL_WORK_CONDITION_VELOCITY, QVariant::Int).add(DBConstants::COL_WORK_CONDITION_ACCELERATION, QVariant::Int).add(DBConstants::COL_WORK_CONDITION_GRIP_CONDITION, QVariant::Int).add(DBConstants::COL_WORK_CONDITION_ACCESSIBILITY, QVariant::Int).add(DBConstants::COL_WORK_CONDITION_GROUND, QVariant::Int).add(DBConstants::COL_WORK_CONDITION_LIGHTING, QVariant::Int).add(DBConstants::COL_WORK_CONDITION_CLIMATE, QVariant::Int).add(DBConstants::COL_WORK_CONDITION_WIND, QVariant::Int).add(DBConstants::COL_WORK_CONDITION_CLOTHING, QVariant::Int).add(DBConstants::COL_WORK_CONDITION_VIBRATION, QVariant::Int).add(DBConstants::COL_WORK_CONDITION_ROOM_TO_MOVE, QVariant::Int).add(DBConstants::COL_WORK_CONDITION_HEAD_SUPPORTED, QVariant::Int).add(DBConstants::COL_WORK_CONDITION_RIGHT_UPPER_ARM_SUPPORTED, QVariant::Int).add(DBConstants::COL_WORK_CONDITION_LEFT_UPPER_ARM_SUPPORTED, QVariant::Int).add(DBConstants::COL_WORK_CONDITION_RIGHT_FOREARM_SUPPORTED, QVariant::Int).add(DBConstants::COL_WORK_CONDITION_LEFT_FOREARM_SUPPORTED, QVariant::Int).add(DBConstants::COL_WORK_CONDITION_RIGHT_HAND_SUPPORTED, QVariant::Int).add(DBConstants::COL_WORK_CONDITION_LEFT_HAND_SUPPORTED, QVariant::Int).add(DBConstants::COL_WORK_CONDITION_RIGHT_THIGH_SUPPORTED, QVariant::Int).add(DBConstants::COL_WORK_CONDITION_TRUNK_SUPPORT, QVariant::Int).add(DBConstants::COL_WORK_CONDITION_LEFT_THIGH_SUPPORTED, QVariant::Int).add(DBConstants::COL_WORK_CONDITION_RIGHT_LOWER_LEG_SUPPORTED, QVariant::Int).add(DBConstants::COL_WORK_CONDITION_LEFT_LOWER_LEG_SUPPORTED, QVariant::Int).build();

//Connection
const QString DBConstants::TBL_CONNECTION = "Connection";
const QString DBConstants::COL_CONNECTION_ID = "connection_ID";
const QString DBConstants::COL_CONNECTION_NAME = "name";
const QString DBConstants::COL_CONNECTION_USERNAME = "username";
const QString DBConstants::COL_CONNECTION_PASSWORD = "password";
const QString DBConstants::COL_CONNECTION_SERVER_ADDRESS = "server_address";
const QString DBConstants::COL_CONNECTION_PORT = "port";
const QString DBConstants::COL_CONNECTION_DEFAULT = "default";
const QString DBConstants::COL_CONNECTION_ANALYST_ID = "analyst_ID";
const QHash<QString, QVariant::Type> DBConstants::HASH_CONNECTION_TYPES = QHashBuilder<QString, QVariant::Type>().add(DBConstants::COL_CONNECTION_ID, QVariant::Int).add(DBConstants::COL_CONNECTION_NAME, QVariant::String).add(DBConstants::COL_CONNECTION_USERNAME, QVariant::String).add(DBConstants::COL_CONNECTION_PASSWORD, QVariant::String).add(DBConstants::COL_CONNECTION_SERVER_ADDRESS, QVariant::String).add(DBConstants::COL_CONNECTION_PORT, QVariant::Int).add(DBConstants::COL_CONNECTION_DEFAULT, QVariant::Bool).add(DBConstants::COL_CONNECTION_ANALYST_ID, QVariant::Int).build();

//Table list
//const QHash<QString, DB_TABLES> DBConstants::HASH_TBL_TO_DB_TABLES = QHashBuilder<QString, DB_TABLES>().add(DBConstants::TBL_ACTIVITY, DB_TABLES::ACTIVITY).add(DBConstants::TBL_ANALYST, DB_TABLES::ANALYST).add(DBConstants::TBL_APPLIED_FORCE, DB_TABLES::APPLIED_FORCE).add(DBConstants::TBL_BODY_POSTURE, DB_TABLES::BODY_POSTURE).add(DBConstants::TBL_BRANCH_OF_INDUSTRY, DB_TABLES::BRANCH_OF_INDUSTRY).add(DBConstants::TBL_BREAK, DB_TABLES::BREAK).add(DBConstants::TBL_COMMENT, DB_TABLES::COMMENT).add(DBConstants::TBL_CORPORATION, DB_TABLES::CORPORATION).add(DBConstants::TBL_EMPLOYEE, DB_TABLES::EMPLOYEE).add(DBConstants::TBL_EMPLOYEE_WORKS_SHIFT, DB_TABLES::EMPLOYEE_WORKS_SHIFT).add(DBConstants::TBL_EMPLOYER, DB_TABLES::EMPLOYER).add(DBConstants::TBL_EQUIPMENT, DB_TABLES::EQUIPMENT).add(DBConstants::TBL_FACTORY, DB_TABLES::FACTORY).add(DBConstants::TBL_LINE, DB_TABLES::LINE).add(DBConstants::TBL_LOAD_HANDLING, DB_TABLES::LOAD_HANDLING).add(DBConstants::TBL_LOAD_HANDLING_TYPE, DB_TABLES::LOAD_HANDLING_TYPE).add(DBConstants::TBL_PRODUCT, DB_TABLES::PRODUCT).add(DBConstants::TBL_RECORDING, DB_TABLES::RECORDING).add(DBConstants::TBL_RECORDING_OB_LINE, DB_TABLES::RECORDING_OBSERVES_LINE).add(DBConstants::TBL_RECORDING_OB_WORKPLACE, DB_TABLES::RECORDING_OBSERVES_WORKPLACE).add(DBConstants::TBL_SHIFT, DB_TABLES::SHIFT).add(DBConstants::TBL_TRANSPORTATION, DB_TABLES::TRANSPORTATION).add(DBConstants::TBL_TYPE_OF_GRASPING, DB_TABLES::TYPE_OF_GRASPING).add(DBConstants::TBL_WORKPLACE, DB_TABLES::WORKPLACE).add(DBConstants::TBL_WORK_CONDITION, DB_TABLES::WORK_CONDITION).add(DBConstants::TBL_WORK_PROCESS, DB_TABLES::WORK_PROCESS).add(DBConstants::TBL_CONNECTION, DB_TABLES::CONNECTION).add(DBConstants::TBL_BODY_MEASUREMENT, DB_TABLES::BODY_MEASUREMENT).build();
const QList<QString> DBConstants::LIST_TABLE_NAMES = QList<QString>()<<DBConstants::TBL_ACTIVITY<<DBConstants::TBL_ANALYST<<DBConstants::TBL_APPLIED_FORCE<<DBConstants::TBL_BODY_POSTURE<<DBConstants::TBL_BRANCH_OF_INDUSTRY<<DBConstants::TBL_BREAK<<DBConstants::TBL_COMMENT<<DBConstants::TBL_CORPORATION<<DBConstants::TBL_EMPLOYEE<<DBConstants::TBL_EMPLOYEE_WORKS_SHIFT<<DBConstants::TBL_EMPLOYER<<DBConstants::TBL_EQUIPMENT<<DBConstants::TBL_FACTORY<<DBConstants::TBL_LINE<<DBConstants::TBL_LOAD_HANDLING<<DBConstants::TBL_LOAD_HANDLING_TYPE<<DBConstants::TBL_PRODUCT<<DBConstants::TBL_RECORDING<<DBConstants::TBL_RECORDING_OB_LINE<<DBConstants::TBL_RECORDING_OB_WORKPLACE<<DBConstants::TBL_SHIFT<<DBConstants::TBL_TRANSPORTATION<<DBConstants::TBL_TYPE_OF_GRASPING<<DBConstants::TBL_WORKPLACE<<DBConstants::TBL_WORK_CONDITION<<DBConstants::TBL_WORK_PROCESS<<DBConstants::TBL_CONNECTION<<DBConstants::TBL_BODY_MEASUREMENT;

