#ifndef IANALYSTLIST
#define IANALYSTLIST

#include <QtPlugin>

class IAnalystList{

public slots:
    virtual void addAnalyst(QHash<QString, QVariant> values) = 0;
    virtual void updateAnalyst(QHash<QString, QVariant> values) = 0;
    virtual void removeAnalyst(int id) = 0;
    virtual void clearAnalysts() = 0;

signals:
    virtual void createAnalyst(QHash<QString, QVariant> values) = 0;
    virtual void deleteAnalyst(int id) = 0;
    virtual void selectAnalyst(int id) = 0;

};

#define IAnalystList_iid "IAnalystList"

Q_DECLARE_INTERFACE(IAnalystList, IAnalystList_iid)

#endif // IANALYSTLIST

