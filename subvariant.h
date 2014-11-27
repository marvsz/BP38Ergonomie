#ifndef SUBVARIANT_H
#define SUBVARIANT_H

#include <QObject>
#include <list>
#include "enums.h"
#include <QString>



class SubVariant
{

public:
    SubVariant(QString *desc, int min, int max, QVector<int> *btnValues, QString* iconPath, VariantControl controlType);
    ~SubVariant();


    QString *getDescription() const;
    int getMin() const;
    int getMax() const;
    QVector<int> *getBtnValues() const;
    VariantControl getControlType() const;
    QString* getIconPath() const;

private:
    QString *desc;
    int min;
    int max;
    QVector<int> *btnValues;
    QString* iconPath;
    VariantControl controlType;

};

#endif // SUBVARIANT_H
