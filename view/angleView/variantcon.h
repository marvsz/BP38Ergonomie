#ifndef VARIANTCON_H
#define VARIANTCON_H

#include <QWidget>
#include <QVector>
#include <QString>
#include <QLabel>
#include <QGroupBox>
#include <QVBoxLayout>
#include "selectablevaluebutton.h"
#include "variantspecification.h"
#include "variant.h"

class VariantCon : public QWidget
{
    Q_OBJECT
public:
    explicit VariantCon(QWidget *parent = 0);

    void addVariant(Variant *variant);
    void setVariantSpecification(VariantSpecification* varSpeci);
    Variant* getVariantByID(int id) const;

signals:
    void selectedVariantChanged(int id);

public slots:
     void selectID(int ID);
     void selectSpecification(int id);

private slots:
    void variantBtnPressed(int id);
    void variantSpeciBtnPressed(int id);


private:
    QVBoxLayout *mainLayout;
    QVBoxLayout *varSpeciLayout;
    QVBoxLayout *varLayout;
    VariantSpecification *varSpeci;
    QVector<SelectableValueButton*> *varSpeciBtns;
    QVector<SelectableValueButton*> *variantBtns;
    QVector<Variant*> *variants;


    int currentSelBtnID;
    int currentSelVarSpeciBtnID;

};

#endif // VARIANTCON_H