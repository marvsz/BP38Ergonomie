#include "xmlparser.h"

XMLParser::XMLParser(QObject *parent) : QObject(parent)
{

}

XMLParser::~XMLParser()
{

}

//PUBLIC METHODS
void XMLParser::parseTransportations(const QString path){
    QFile *file = new QFile(path);
    if(file->exists()){
        if(file->open(QIODevice::ReadWrite)){
            QXmlStreamReader xmlReader;
            xmlReader.setDevice(file);

            while(!xmlReader.atEnd() && !xmlReader.hasError()){
                QXmlStreamReader::TokenType token = xmlReader.readNext();

                if(token == QXmlStreamReader::StartDocument)
                    continue;

                if(token == QXmlStreamReader::StartElement){
                    if(xmlReader.name().compare(XMLConstants::TRANSPORTATIONS) == 0)
                        continue;

                    else if(xmlReader.name().compare(XMLConstants::TRANSPORTATION) == 0)
                        parseTransportation(xmlReader);
                }
            }

            xmlReader.clear();
            file->close();
            file->remove();
        }
    }
}

void XMLParser::parseEquipments(const QString path){
    QFile *file = new QFile(path);
    if(file->exists()){
        if(file->open(QIODevice::ReadWrite)){
            QXmlStreamReader xmlReader;
            xmlReader.setDevice(file);

            while(!xmlReader.atEnd() && !xmlReader.hasError()){
                QXmlStreamReader::TokenType token = xmlReader.readNext();

                if(token == QXmlStreamReader::StartDocument)
                    continue;

                if(token == QXmlStreamReader::StartElement){
                    if(xmlReader.name().compare(XMLConstants::EQUIPMENTS) == 0)
                        continue;

                    else if(xmlReader.name().compare(XMLConstants::EQUIPMENT) == 0)
                        parseEquipment(xmlReader);
                }
            }

            xmlReader.clear();
            file->close();
            file->remove();
        }
    }
}

void XMLParser::parseProducts(const QString path){
    QFile *file = new QFile(path);
    if(file->exists()){
        if(file->open(QIODevice::ReadWrite)){
            QXmlStreamReader xmlReader;
            xmlReader.setDevice(file);

            while(!xmlReader.atEnd() && !xmlReader.hasError()){
                QXmlStreamReader::TokenType token = xmlReader.readNext();

                if(token == QXmlStreamReader::StartDocument)
                    continue;

                if(token == QXmlStreamReader::StartElement){
                    if(xmlReader.name().compare(XMLConstants::PRODUCTS) == 0)
                        continue;

                    else if(xmlReader.name().compare(XMLConstants::PRODUCT) == 0)
                        parseProduct(xmlReader);
                }
            }

            xmlReader.clear();
            file->close();
            file->remove();
        }
    }
}

void XMLParser::parseEmployees(const QString path){
    QFile *file = new QFile(path);
    if(file->exists()){
        if(file->open(QIODevice::ReadWrite)){
            QXmlStreamReader xmlReader;
            xmlReader.setDevice(file);

            while(!xmlReader.atEnd() && !xmlReader.hasError()){
                QXmlStreamReader::TokenType token = xmlReader.readNext();

                if(token == QXmlStreamReader::StartDocument)
                    continue;

                if(token == QXmlStreamReader::StartElement){
                    if(xmlReader.name().compare(XMLConstants::EMPLOYEES) == 0)
                        continue;

                    else if(xmlReader.name().compare(XMLConstants::EMPLOYEE) == 0)
                        parseEmployee(xmlReader);
                }
            }

            xmlReader.clear();
            file->close();
            file->remove();
        }
    }
}

void XMLParser::parseWorkplaces(const QString path){
    QFile *file = new QFile(path);
    if(file->exists()){
        if(file->open(QIODevice::ReadWrite)){
            QXmlStreamReader xmlReader;
            xmlReader.setDevice(file);

            while(!xmlReader.atEnd() && !xmlReader.hasError()){
                QXmlStreamReader::TokenType token = xmlReader.readNext();

                if(token == QXmlStreamReader::StartDocument)
                    continue;

                if(token == QXmlStreamReader::StartElement){
                    if(xmlReader.name().compare(XMLConstants::WORKPLACES) == 0)
                        continue;

                    else if(xmlReader.name().compare(XMLConstants::WORKPLACE) == 0)
                        parseWorkplace(xmlReader);
                }
            }

            xmlReader.clear();
            file->close();
            file->remove();
        }
    }
}

//PRIVATE METHODS
//Transportation parsing
void XMLParser::parseTransportation(QXmlStreamReader &xmlReader){
    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    xmlReader.readNext();
    while(!(xmlReader.tokenType() == QXmlStreamReader::EndElement && xmlReader.name().compare(XMLConstants::TRANSPORTATION) == 0)){
        if(xmlReader.tokenType() == QXmlStreamReader::StartElement){
            if(xmlReader.name().compare(XMLConstants::TRANSPORTATION_NAME) == 0)
                addElementDataToHash(xmlReader, DBConstants::COL_TRANSPORTATION_NAME, values);
            else if(xmlReader.name().compare(XMLConstants::TRANSPORTATION_FIXED_ROLLER) == 0)
                addElementDataToHash(xmlReader, DBConstants::COL_TRANSPORTATION_FIXED_ROLLER, values);
            else if(xmlReader.name().compare(XMLConstants::TRANSPORTATION_BRAKES) == 0)
                addElementDataToHash(xmlReader, DBConstants::COL_TRANSPORTATION_BRAKES, values);
            else if(xmlReader.name().compare(XMLConstants::TRANSPORTATION_EMPTY_WEIGHT) == 0)
                addElementDataToHash(xmlReader, DBConstants::COL_TRANSPORTATION_EMPTY_WEIGHT, values);
            else if(xmlReader.name().compare(XMLConstants::TRANSPORTATION_MAX_LOAD) == 0)
                addElementDataToHash(xmlReader, DBConstants::COL_TRANSPORTATION_MAX_LOAD, values);
        }
        xmlReader.readNext();
    }
    emit createTransportation(values);
}

//Equipment parsing
void XMLParser::parseEquipment(QXmlStreamReader &xmlReader){
    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    xmlReader.readNext();
    while(!(xmlReader.tokenType() == QXmlStreamReader::EndElement && xmlReader.name().compare(XMLConstants::EQUIPMENT) == 0)){
        if(xmlReader.tokenType() == QXmlStreamReader::StartElement){
            if(xmlReader.name().compare(XMLConstants::EQUIPMENT_NAME) == 0)
                addElementDataToHash(xmlReader, DBConstants::COL_EQUIPMENT_NAME, values);
            else if(xmlReader.name().compare(XMLConstants::EQUIPMENT_RECOIL_COUNT) == 0)
                addElementDataToHash(xmlReader, DBConstants::COL_EQUIPMENT_RECOIL_COUNT, values);
            else if(xmlReader.name().compare(XMLConstants::EQUIPMENT_RECOIL_INTENSITY) == 0)
                addElementDataToHash(xmlReader, DBConstants::COL_EQUIPMENT_RECOIL_INTENSITY, values);
            else if(xmlReader.name().compare(XMLConstants::EQUIPMENT_VIBRATION_COUNT) == 0)
                addElementDataToHash(xmlReader, DBConstants::COL_EQUIPMENT_VIBRATION_COUNT, values);
            else if(xmlReader.name().compare(XMLConstants::EQUIPMENT_VIBRATION_INTENSITY) == 0)
                addElementDataToHash(xmlReader, DBConstants::COL_EQUIPMENT_VIBRATION_INTENSITY, values);
        }
        xmlReader.readNext();
    }
    emit createEquipment(values);
}

//Product parsing
void XMLParser::parseProduct(QXmlStreamReader &xmlReader){
    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    xmlReader.readNext();
    while(!(xmlReader.tokenType() == QXmlStreamReader::EndElement && xmlReader.name().compare(XMLConstants::PRODUCT) == 0)){
        if(xmlReader.tokenType() == QXmlStreamReader::StartElement){
            if(xmlReader.name().compare(XMLConstants::PRODUCT_NAME) == 0)
                addElementDataToHash(xmlReader, DBConstants::COL_PRODUCT_NAME, values);
            else if(xmlReader.name().compare(XMLConstants::PRODUCT_NUMBER) == 0)
                addElementDataToHash(xmlReader, DBConstants::COL_PRODUCT_NUMBER, values);
            else if(xmlReader.name().compare(XMLConstants::PRODUCT_TOTAL_PERCENTAGE) == 0)
                addElementDataToHash(xmlReader, DBConstants::COL_PRODUCT_TOTAL_PERCENTAGE, values);
        }
        xmlReader.readNext();
    }
    emit createProduct(values);
}

//Employee parsing
void XMLParser::parseEmployee(QXmlStreamReader &xmlReader){
    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    QHash<QString, QVariant> bodyMeasurementValues = QHash<QString, QVariant>();

    xmlReader.readNext();
    while(!(xmlReader.tokenType() == QXmlStreamReader::EndElement && xmlReader.name().compare(XMLConstants::EMPLOYEE) == 0)){
        if(xmlReader.tokenType() == QXmlStreamReader::StartElement){
            if(xmlReader.name().compare(XMLConstants::EMPLOYEE_STAFF_NUMBER) == 0)
                addElementDataToHash(xmlReader, DBConstants::COL_EMPLOYEE_STAFF_NUMBER, values);
            else if(xmlReader.name().compare(XMLConstants::EMPLOYEE_AGE) == 0)
                addElementDataToHash(xmlReader, DBConstants::COL_EMPLOYEE_AGE, values);
            else if(xmlReader.name().compare(XMLConstants::EMPLOYEE_GENDER) == 0)
                addElementDataToHash(xmlReader, DBConstants::COL_EMPLOYEE_GENDER, values);
            else if(xmlReader.name().compare(XMLConstants::EMPLOYEE_HEIGHT) == 0)
                addElementDataToHash(xmlReader, DBConstants::COL_EMPLOYEE_HEIGHT, values);
            else if(xmlReader.name().compare(XMLConstants::EMPLOYEE_NOTE) == 0)
                addElementDataToHash(xmlReader, DBConstants::COL_EMPLOYEE_NOTE, values);
            else if(xmlReader.name().compare(XMLConstants::EMPLOYEE_BODY_MEASUREMENT) == 0)
                bodyMeasurementValues = parseBodyMeasurement(xmlReader);
        }
        xmlReader.readNext();
    }
    emit createEmployee(values, bodyMeasurementValues);
}

QHash<QString, QVariant> XMLParser::parseBodyMeasurement(QXmlStreamReader &xmlReader){
    QHash<QString, QVariant> values = QHash<QString, QVariant>();

    xmlReader.readNext();
    while(!(xmlReader.tokenType() == QXmlStreamReader::EndElement && xmlReader.name().compare(XMLConstants::EMPLOYEE_BODY_MEASUREMENT) == 0)){
        if(xmlReader.tokenType() == QXmlStreamReader::StartElement){
            if(xmlReader.name().compare(XMLConstants::EMPLOYEE_BODY_MEASUREMENT_FOOT_LENGTH) == 0)
                addElementDataToHash(xmlReader, DBConstants::COL_BODY_MEASUREMENT_FOOT_LENGTH, values);
            else if(xmlReader.name().compare(XMLConstants::EMPLOYEE_BODY_MEASUREMENT_FOREARM_LENGTH) == 0)
                addElementDataToHash(xmlReader, DBConstants::COL_BODY_MEASUREMENT_FOREARM_LENGTH, values);
            else if(xmlReader.name().compare(XMLConstants::EMPLOYEE_BODY_MEASUREMENT_HAND_LENGTH_GRIP_AXIS) == 0)
                addElementDataToHash(xmlReader, DBConstants::COL_BODY_MEASUREMENT_HAND_LENGTH_GRIP_AXIS, values);
            else if(xmlReader.name().compare(XMLConstants::EMPLOYEE_BODY_MEASUREMENT_HEAD_NECK_HEIGHT) == 0)
                addElementDataToHash(xmlReader, DBConstants::COL_BODY_MEASUREMENT_HEAD_NECK_HEIGHT, values);
            else if(xmlReader.name().compare(XMLConstants::EMPLOYEE_BODY_MEASUREMENT_SHOULDER_WIDTH) == 0)
                addElementDataToHash(xmlReader, DBConstants::COL_BODY_MEASUREMENT_SHOULDER_WIDTH, values);
            else if(xmlReader.name().compare(XMLConstants::EMPLOYEE_BODY_MEASUREMENT_SHOULDER_WIDTH_BIACROMIAL) == 0)
                addElementDataToHash(xmlReader, DBConstants::COL_BODY_MEASUREMENT_SHOULDER_WIDTH_BIACROMIAL, values);
            else if(xmlReader.name().compare(XMLConstants::EMPLOYEE_BODY_MEASUREMENT_SHOULDER_WIDTH_BIDELTOID) == 0)
                addElementDataToHash(xmlReader, DBConstants::COL_BODY_MEASUREMENT_SHOULDER_WIDTH_BIDELTOID, values);
            else if(xmlReader.name().compare(XMLConstants::EMPLOYEE_BODY_MEASUREMENT_THIGHT_HEIGHT) == 0)
                addElementDataToHash(xmlReader, DBConstants::COL_BODY_MEASUREMENT_THIGH_LENGTH, values);
            else if(xmlReader.name().compare(XMLConstants::EMPLOYEE_BODY_MEASUREMENT_TIBIAL_HEIGHT) == 0)
                addElementDataToHash(xmlReader, DBConstants::COL_BODY_MEASUREMENT_TIBIAL_HEIGHT, values);
            else if(xmlReader.name().compare(XMLConstants::EMPLOYEE_BODY_MEASUREMENT_TORSO_HEIGHT) == 0)
                addElementDataToHash(xmlReader, DBConstants::COL_BODY_MEASUREMENT_TORSO_HEIGHT, values);
            else if(xmlReader.name().compare(XMLConstants::EMPLOYEE_BODY_MEASUREMENT_UPPER_ARM_LENGTH) == 0)
                addElementDataToHash(xmlReader, DBConstants::COL_BODY_MEASUREMENT_UPPER_ARM_LENGTH, values);
        }
        xmlReader.readNext();
    }
    return values;
}

//Parse Workplaces
void XMLParser::parseWorkplace(QXmlStreamReader &xmlReader){
    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    QList<QHash<QString, QVariant>> activityValues = QList<QHash<QString, QVariant>>();

    xmlReader.readNext();
    while(!(xmlReader.tokenType() == QXmlStreamReader::EndElement && xmlReader.name().compare(XMLConstants::WORKPLACE) == 0)){
        if(xmlReader.tokenType() == QXmlStreamReader::StartElement){
            if(xmlReader.name().compare(XMLConstants::WORKPLACE_NAME) == 0)
                addElementDataToHash(xmlReader, DBConstants::COL_WORKPLACE_NAME, values);
            else if(xmlReader.name().compare(XMLConstants::WORKPLACE_DESCRIPTION) == 0)
                addElementDataToHash(xmlReader, DBConstants::COL_WORKPLACE_DESCRIPTION, values);
            else if(xmlReader.name().compare(XMLConstants::WORKPLACE_PERCENTAGE_WOMAN) == 0)
                addElementDataToHash(xmlReader, DBConstants::COL_WORKPLACE_PERCENTAGE_WOMAN, values);
            else if(xmlReader.name().compare(XMLConstants::WORKPLACE_CODE) == 0)
                addElementDataToHash(xmlReader, DBConstants::COL_WORKPLACE_CODE, values);
            else if(xmlReader.name().compare(XMLConstants::WORKPLACE_CYCLE_TIME) == 0)
                addElementDataToHash(xmlReader, DBConstants::COL_WORKPLACE_CYCLE_TIME, values);
            else if(xmlReader.name().compare(XMLConstants::WORKPLACE_SETUP_TIME) == 0)
                addElementDataToHash(xmlReader, DBConstants::COL_WORKPLACE_SETUP_TIME, values);
            else if(xmlReader.name().compare(XMLConstants::WORKPLACE_BASIC_TIME) == 0)
                addElementDataToHash(xmlReader, DBConstants::COL_WORKPLACE_BASIC_TIME, values);
            else if(xmlReader.name().compare(XMLConstants::WORKPLACE_REST_TIME) == 0)
                addElementDataToHash(xmlReader, DBConstants::COL_WORKPLACE_REST_TIME, values);
            else if(xmlReader.name().compare(XMLConstants::WORKPLACE_ALLOWANCE_TIME) == 0)
                addElementDataToHash(xmlReader, DBConstants::COL_WORKPLACE_ALLOWANCE_TIME, values);
            else if(xmlReader.name().compare(XMLConstants::WORKPLACE_ACTIVITIES) == 0)
                activityValues = parseActivities(xmlReader);
        }
        xmlReader.readNext();
    }
    emit createWorkplace(values, activityValues);
}

QList<QHash<QString, QVariant>> XMLParser::parseActivities(QXmlStreamReader &xmlReader){
    QList<QHash<QString, QVariant>> activityValues = QList<QHash<QString, QVariant>>();

    xmlReader.readNext();
    while(!(xmlReader.tokenType() == QXmlStreamReader::EndElement && xmlReader.name().compare(XMLConstants::WORKPLACE_ACTIVITIES) == 0)){
        if(xmlReader.tokenType() == QXmlStreamReader::StartElement){
            activityValues.append(parseActivity(xmlReader));
        }
        xmlReader.readNext();
    }
    return activityValues;
}

QHash<QString, QVariant> XMLParser::parseActivity(QXmlStreamReader &xmlReader){
    QHash<QString, QVariant> values = QHash<QString, QVariant>();

    xmlReader.readNext();
    while(!(xmlReader.tokenType() == QXmlStreamReader::EndElement && xmlReader.name().compare(XMLConstants::WORKPLACE_ACTIVITY) == 0)){
        if(xmlReader.tokenType() == QXmlStreamReader::StartElement){
            if(xmlReader.name().compare(XMLConstants::WORKPLACE_ACTIVITY_DESCRIPTION) == 0)
                addElementDataToHash(xmlReader, DBConstants::COL_ACTIVITY_DESCRIPTION, values);
            else if(xmlReader.name().compare(XMLConstants::WORKPLACE_ACTIVITY_REPETITIONS) == 0)
                addElementDataToHash(xmlReader, DBConstants::COL_ACTIVITY_REPETITIONS, values);
            else if(xmlReader.name().compare(XMLConstants::WORKPLACE_ACTIVITY_PRODUCTNAME) == 0)
                addElementDataToHash(xmlReader, DBConstants::COL_PRODUCT_NAME, values);
        }
        xmlReader.readNext();
    }
    return values;
}

//General auxiliary functions
void XMLParser::addElementDataToHash(QXmlStreamReader &xmlReader, const QString &key, QHash<QString, QVariant> &values){
    if(xmlReader.tokenType() == QXmlStreamReader::StartElement) {
         xmlReader.readNext();
         if(xmlReader.tokenType() == QXmlStreamReader::Characters) {
             values.insert(key, xmlReader.text().toString());
         }
    }
}

// GETTER
QString XMLParser::getModeName() const{
    return "XML";
}
IImportDataParser::FileMode XMLParser::getFileMode() const{
    return IImportDataParser::FileMode::MultiFile;
}

QString XMLParser::getSingleFilename() const{
    return "";
}

QString XMLParser::getTransportationFilename() const{
    return XMLConstants::FILENAME_TRANSPORTATIONS;
}
QString XMLParser::getEquipmentFilename() const{
    return XMLConstants::FILENAME_EQUIPMENTS;
}
QString XMLParser::getProductFilename() const{
    return XMLConstants::FILENAME_PRODUCTS;
}
QString XMLParser::getEmployeeFilename() const{
    return XMLConstants::FILENAME_EMPLOYEES;
}
QString XMLParser::getWorkplaceFilename() const{
    return XMLConstants::FILENAME_WORKPLACES;
}
