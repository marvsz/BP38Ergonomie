#ifndef QUICKARMPOSTURECONTROL_H
#define QUICKARMPOSTURECONTROL_H

#include <QWidget>
#include <QVBoxLayout>
#include <QStringList>
#include <QVariant>
#include "selectablevaluebutton.h"
#include <QString>

class QuickArmPostureControl : public QWidget
{ Q_OBJECT
public:
    explicit QuickArmPostureControl(QWidget *parent=0);

    QVariant getSelectedValue() const;
    QString getSelectedTexts() const;
    int getSelectedID() const;
    int getSelectedSpecification() const;

signals:
    void selectionChanged(int id, int sel);
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


#endif // QUICKARMPOSTURECONTROL_H
