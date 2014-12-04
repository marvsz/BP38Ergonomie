#ifndef VARIANT_H
#define VARIANT_H

#include <QString>
#include <QVector>
#include "subvariant.h"

class Variant
{
public:
    Variant(QString* desc, SubVariant* subVariant);
    ~Variant();

    QString *getDescription() const;
    std::vector<SubVariant *> *getSubVariants() const;
    void addSubVariant(SubVariant *subVariant);

private:
    QString* desc;
    std::vector<SubVariant*> *subVariants;
};

#endif // VARIANT_H
