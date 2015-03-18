#ifndef IIMPORTDATA
#define IIMPORTDATA

#include <QtPlugin>
#include "iftpconnections.h"

class IImportData : public IFTPConnections
{

public:
    virtual QString getImportMode() const = 0;
    virtual bool importTransportations() const = 0;
    virtual bool importEquipments() const = 0;
    virtual bool importProducts() const = 0;
    virtual bool importEmployees() const = 0;
    virtual bool importWorkplaces() const = 0;

signals:
    virtual void importData(IImportData *widget) = 0;

};

#define IImportData_iid "IImportData"

Q_DECLARE_INTERFACE(IImportData, IImportData_iid)

#endif // IIMPORTDATA

