#ifndef ANGLECONTROL_H
#define ANGLECONTROL_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QVector>
#include <QString>
#include <QLabel>
#include "owncon.h"
#include "variantcon.h"
#include "variant.h"
#include "seperator.h"
#include "variantspecification.h"

class AngleControl : public QWidget
{
    Q_OBJECT
public:
    explicit AngleControl(QString* descVarConText, Variant* variant, VariantSpecification* varSpeci, QWidget *parent = 0);
    void addVariant(Variant* variant);
    void selectVariant(int id);

signals:

public slots:
    void showContent();
    void hideContent();

private slots:
    void selectedVariantChanged(int id);
    void showHideBtnPressed();

private:
    VariantCon *variantCon;

    QLabel *descLbl;
    QPushButton *showHideBtn;
    QVector<OwnCon*> *ownCons;
    QVector<Seperator*> *ownConSeperator;
    QHBoxLayout *mainHLayout;
    QVBoxLayout *subVariantsLayout;
    QWidget *content;



};

#endif // ANGLECONTROL_H
