#ifndef QUICKLEGPOSTURECONTROL_H
#define QUICKLEGPOSTURECONTROL_H

#include <QWidget>
#include <QVBoxLayout>
#include <QStringList>
#include <QVariant>
#include "selectablevaluebutton.h"
#include <QString>

class QuickLegPostureControl : public QWidget
{
    Q_OBJECT
public:
    explicit QuickLegPostureControl(QWidget *parent=0);

    QVariant getSelectedValue() const;
    QString getSelectedTexts() const;
    int getSelectedID() const;
    int getSelectedSpecification() const;

signals:
    void selectionChanged(int id, int speci);
    void specificationChanged(int id);

public slots:
    void setSelectedValue(int id);
    void setSelectedSpecification(int id);
    void setValues(const QStringList &texts, const QStringList &differ, const QString &label);

private:
    SelectableValueButton *currentSelectedBtn;
    SelectableValueButton *currentSpeciBtn;

    QVector<SelectableValueButton*> btnOptions;
    QVector<SelectableValueButton*> speciOptions;
    QVBoxLayout *mainLayout;

    void clear();

    int id;
    int idSpeci;
    int specification;

};

#endif // QUICKLEGPOSTURECONTROL_H
