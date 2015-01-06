#ifndef VARIANTSPEZIFIKATION_H
#define VARIANTSPEZIFIKATION_H
#include <QString>
#include <QVector>



class VariantSpecification
{
public:
    VariantSpecification();



    void addSpezification(QString *desc);
    QVector<QString *> *getSpecificationDesc();

private:
    QVector<QString*> *speciDescs;
};

#endif // VARIANTSPEZIFIKATION_H
