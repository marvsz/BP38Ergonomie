#ifndef SUBVARIANT_H
#define SUBVARIANT_H

#include "enum.h"
#include <QString>
#include <QVector>


class SubVariant
{

public:
    SubVariant(QString *desc, int min, int max, const QVector<int> &btnValues, QString* iconPath);
    SubVariant(QString *desc, const QVector<QString> &btnTexts, QString* iconPath);
    ~SubVariant();


    QString *getDescription() const;
    int getMin() const;
    int getMax() const;
    const QVector<int> getBtnValues() const;
    const QVector<QString> getBtnTexts() const;
    VariantControl getControlType() const;
    QString* getIconPath() const;

private:
    QString *desc;
    int min;
    int max;
    const QVector<QString> btnTexts;
    const QVector<int> btnValues;
    QString* iconPath;
    VariantControl controlType;

};

#endif // SUBVARIANT_H
