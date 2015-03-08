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
    //void setSelectedLeft(int id);
    //void setSelectedRight(int id);
    /*void setSelectedValue(const QString &text);
    void setSelectedByValue(int value);
    void setValues(const QStringList &texts, const QVector<QVariant> &values);
    void setValues(const QStringList &texts);*/
    void setValues(const QStringList &texts, const QStringList &differ, const QString &label);

private:
    SelectableValueButton *currentSelectedBtn;
    SelectableValueButton *currentSpeciBtn;
    //SelectableValueButton *currentLeftBtn;
    //SelectableValueButton *currentRightBtn;

    QVector<SelectableValueButton*> btnOptions;
    QVector<SelectableValueButton*> speciOptions;
    //QVector<SelectableValueButton*> leftOptions;
    //QVector<SelectableValueButton*> rightOptions;
    QVBoxLayout *mainLayout;

    void clear();

    int id;
    int idSpeci;
    int specification;
    //int idLeft;
    //int idRight;

};

#endif // QUICKLEGPOSTURECONTROL_H
