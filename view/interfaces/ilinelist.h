#ifndef ILINELIST_H
#define ILINELIST_H

#include <QtPlugin>

class ILineList{

signals:
    virtual void createLine(QHash<QString, QVariant> values) = 0;
    virtual void deleteLine(int id) = 0;
    virtual void selectLine(int id) = 0;
    virtual void editLine(int id) = 0;

public slots:
    virtual void addLine(QHash<QString, QVariant> values) = 0;
    virtual void updateLine(QHash<QString, QVariant> values) = 0;
    virtual void removeLine(int id) = 0;
    virtual void selectedLine(QHash<QString, QVariant> values) = 0;
    virtual void clearLines() = 0;

};

#define ILineList_iid "ILineList"

Q_DECLARE_INTERFACE(ILineList, ILineList_iid)
#endif // ILINELIST_H
