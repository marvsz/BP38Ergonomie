#ifndef IEQUIPMENTLIST
#define IEQUIPMENTLIST

#include <QtPlugin>

class IEquipmentList{

signals:
    virtual void createEquipment(QHash<QString, QVariant> values) = 0;
    virtual void deleteEquipment(int id) = 0;
    virtual void selectEquipment(int id) = 0;

public slots:
    virtual void addEquipment(QHash<QString, QVariant> values) = 0;
    virtual void removeEquipment(int id) = 0;
    virtual void updateEquipment(QHash<QString, QVariant> values) = 0;
    virtual void clearEquipments() = 0;

};

#define IEquipmentList_iid "IEquipmentList"
Q_DECLARE_INTERFACE(IEquipmentList, IEquipmentList_iid)

#endif // IEQUIPMENTLIST

