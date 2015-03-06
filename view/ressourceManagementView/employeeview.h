#ifndef EMPLOYEEVIEW_H
#define EMPLOYEEVIEW_H

#include <QWidget>
#include <QLabel>
#include <QVector>
#include <QPushButton>
#include "../optionselectioncontrol.h"
#include "../textedit.h"
#include "../textlineedit.h"
#include "../valuecontrol.h"
#include "../navigation/simplenavigateablewidget.h"
#include "../interfaces/iemployee.h"
#include "../databaseHandler/dbconstants.h"

class EmployeeView : public SimpleNavigateableWidget, IEmployee
{
    Q_OBJECT
    Q_INTERFACES(IEmployee)
public:
    explicit EmployeeView(QWidget *parent = 0);
    ~EmployeeView();

    bool hasAdditionalNavigation() const{
        return true;
    }

    QList<QAbstractButton*> * getAdditionalNavigation() const;

signals:
    void saveEmployee(QHash<QString, QVariant> values);


public slots:
    void setEmployee(QHash<QString, QVariant> values);
    void onLeaving();

private slots:
    void btnBodyMeasurementsClicked();

private:
    QLabel *lblGender;
    QLabel *lblStaffNumber;
    QLabel *lblNote;

    OptionSelectionControl *oscGender;
    ValueControl *vcAge;
    ValueControl *vcHeight;
    TextLineEdit *txtBxStaffNumber;
    TextEdit *txtBxNote;

    QPushButton *btnBodyMeasurements;

    const QStringList genderTextValues = QStringList()<<tr("male")<<tr("female");
    const QVector<int> heightValues = QVector<int>()<<150<<160<<170<<180<<190;
    const QVector<int> ageValues = QVector<int>()<<20<<30<<40<<50<<60;
};

#endif // EMPLOYEEVIEW_H
