#ifndef ITRANSPORTATIONLIST
#define ITRANSPORTATIONLIST

#include <QtPlugin>

class ITransportationList{

signals:
    virtual void createTransportation(QHash<QString, QVariant> values) = 0;
    virtual void deleteTransportation(int id) = 0;
    virtual void selectTransportation(int id) = 0;

public slots:
    virtual void addTransportation(QHash<QString, QVariant> values) = 0;
    virtual void removeTransportation(int id) = 0;
    virtual void updateTransportation(QHash<QString, QVariant> values) = 0;
    virtual void clearTransportations() = 0;

};

#define ITransportationList_iid "ITransportationList"
Q_DECLARE_INTERFACE(ITransportationList, ITransportationList_iid)

#endif // ITRANSPORTATIONLIST

