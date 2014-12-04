#ifndef SUBVARIANT_H
#define SUBVARIANT_H

#include <QObject>
#include <list>
#include "enum.h"
#include <QString>



class SubVariant
{

public:
    SubVariant(QString *desc, int min, int max, QVector<int> *btnValues, QString* iconPath);
    SubVariant(QString *desc, QVector<QString*> *btnTexts, QString* iconPath);
    ~SubVariant();


    QString *getDescription() const;
    int getMin() const;
    int getMax() const;
    QVector<int> *getBtnValues() const;
    QVector<QString*> *getBtnTexts() const;
    VariantControl getControlType() const;
    QString* getIconPath() const;

private:
    QString *desc;
    int min;
    int max;
    QVector<QString*> *btnTexts;
    QVector<int> *btnValues;
    QString* iconPath;
    VariantControl controlType;

};

#endif // SUBVARIANT_H
