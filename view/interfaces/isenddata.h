#ifndef ISENDDATA
#define ISENDDATA

#include <QtPlugin>
#include "iftpconnections.h"

class ISendData : public IFTPConnections
{

signals:
    virtual void sendData(ISendData *widget) = 0;

};

#define ISendData_iid "ISendData"

Q_DECLARE_INTERFACE(ISendData, ISendData_iid)

#endif // ISENDDATA

