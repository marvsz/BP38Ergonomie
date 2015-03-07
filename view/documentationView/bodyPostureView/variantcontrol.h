#ifndef VARIANTCONTROL_H
#define VARIANTCONTROL_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "../../selectablevaluebutton.h"
#include "../../valuecontrol.h"
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

    void setSelectedSpecification(AVType type);


    QString getName() const;
    int getValue(int variantID, int subVariantID) const;
    QString getTextValue(int variantID, int subVariantID) const;

signals:
    void valueChanged(int type, const QVariant &value);
    void valueChanged(const QVariant &value);
    void requestShowContent(const QString &name);

public slots:
    void hideContent();
    void showContent();
    void setName(const QString &name);
    void setButtonIcon(const QString &objectName, const QSize &size);
    void setSelectedVariant(int variantID);
    void setExclusiveDisplayByName(const QString &name);

private slots:
    void btnVariantClicked(int id);
    void vcValueChanged(const QVariant &value);
    void btnNameClicked();
private:
    QString name;
    QVBoxLayout *variantsLayout;
    QVBoxLayout *valueControlLayout;
    QWidget *mainContent;

    QPushButton *btnName;

    VariantSpecification *varSpeci;
    bool hasSpeci;

    SelectableValueButton *svBtnCurrentSel;
    QVector<QVector<ValueControl*>*> *valueControls;
    QVector<SelectableValueButton*> *variantBtns;

    bool shown;
};

#endif // VARIANTCONTROL_H
