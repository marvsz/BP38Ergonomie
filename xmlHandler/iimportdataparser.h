#ifndef IIMPORTDATAPARSER
#define IIMPORTDATAPARSER

#include <QtPlugin>

class IImportDataParser{
public:
    enum FileMode {SingleFile, MultiFile};

    virtual QString getModeName() const = 0;
    virtual FileMode getFileMode() const = 0;

    virtual QString getTransportationFilename() const = 0;
    virtual QString getEquipmentFilename() const = 0;
    virtual QString getProductFilename() const = 0;
    virtual QString getEmployeeFilename() const = 0;
    virtual QString getWorkplaceFilename() const = 0; 
    virtual QString getSingleFilename() const = 0;

    virtual void parseTransportations(const QString path) = 0;
    virtual void parseEquipments(const QString path) = 0;
    virtual void parseProducts(const QString path) = 0;
    virtual void parseEmployees(const QString path) = 0;
    virtual void parseWorkplaces(const QString path) = 0;

signals:
    virtual void createTransportation(QHash<QString, QVariant> values) = 0;
    virtual void createEquipment(QHash<QString, QVariant> values) = 0;
    virtual void createProduct(QHash<QString, QVariant> values) = 0;
    virtual void createEmployee(QHash<QString, QVariant> values, QHash<QString, QVariant> bodyMeasurementValues) = 0;
    virtual void createWorkplace(QHash<QString, QVariant> values, QList<QHash<QString, QVariant>> activityValues) = 0;

};

#define IImportDataParser_iid "IImportDataParser"

Q_DECLARE_INTERFACE(IImportDataParser, IImportDataParser_iid)

#endif // IIMPORTDATAPARSER

