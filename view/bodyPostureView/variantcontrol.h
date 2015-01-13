#ifndef VARIANTCONTROL_H
#define VARIANTCONTROL_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "selectablevaluebutton.h"
#include "valuecontrol.h"
#include "variantspecification.h"

class VariantControl : public QWidget
{
    Q_OBJECT
public:
    explicit VariantControl(QWidget *parent = 0);
    ~VariantControl();

    int addVariant(const QString &name);
    int addSubVariant(int variantID, ValueControl *vc);

    void setSpecification(VariantSpecification *varSpeci);

    void setSelectedSpecification(int speciID);


    QString getName() const;
    int getValue(int variantID, int subVariantID) const;
    QString getTextValue(int variantID, int subVariantID) const;

signals:
    void valueChanged(int type, const QVariant &value);
    void valueChanged(const QVariant &value);

public slots:
    void hideContent();
    void showContent();
    void setName(const QString &name);
    void setSelectedVariant(int variantID);

private slots:
    void btnVariantClicked(int id, SelectableValueButton *btn);
    void vcValueChanged(const QVariant &value);

private:
    QVBoxLayout *variantsLayout;
    QVBoxLayout *valueControlLayout;
    QWidget *mainContent;

    QPushButton *btnName;

    VariantSpecification *varSpeci;

    SelectableValueButton *svBtnCurrentSel;
    QVector<QVector<ValueControl*>*> *valueControls;

};

#endif // VARIANTCONTROL_H
