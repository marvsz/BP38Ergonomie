#ifndef VARIANTSPEZIFIKATION_H
#define VARIANTSPEZIFIKATION_H

#include <QWidget>
#include <QVBoxLayout>
#include <QVector>
#include "../../selectablevaluebutton.h"

class VariantSpecification : public QWidget
{
    Q_OBJECT
public:
    explicit VariantSpecification(QWidget *parent = 0);

    void addSpecification(const QString &name, int id, int value = 0);

    int getValue(int id);
    int getSelectedID() const;

signals:
    void selectedSpeciValueChanged(int value);

public slots:
    void setSelected(int id);

private slots:
    void btnSpeciClicked(int id);

private:
    QVBoxLayout *mainContent;
    QVector<SelectableValueButton*> speciBtns;
    SelectableValueButton *selCurBtn;

    SelectableValueButton* getSpeciBtnByID(int id);
};

#endif // VARIANTSPEZIFIKATION_H
