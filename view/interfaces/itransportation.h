#ifndef ITRANSPORTATION
#define ITRANSPORTATION

#include <QtPlugin>

class ITransportation{

signals:
    virtual void saveTransportation(QHash<QString, QVariant> values) = 0;

public slots:
    virtual void setTransportation(QHash<QString, QVariant> values) = 0;

};

#define ITransportation_iid "ITransportation"
Q_DECLARE_INTERFACE(ITransportation, ITransportation_iid)

#endif // ITRANSPORTATION

