#ifndef EMPLOYEEVIEW_H
#define EMPLOYEEVIEW_H

#include <QWidget>
#include <QLabel>
#include <QVector>
#include <QPushButton>
#include "optionselectioncontrol.h"
#include "textedit.h"
#include "textlineedit.h"
#include "valuecontrol.h"

class EmployeeView : public QWidget
{
    Q_OBJECT
public:
    explicit EmployeeView(QWidget *parent = 0);
    ~EmployeeView();

    int getGender() const;
    int getAge() const;
    int getHeight() const;
    QString getStaffNumber() const;
    QString getNote() const;

signals:
    void back();
    void save();
    void showBodyMeasurementView();

public slots:
    void setEmployee(int gender, int age, int height, const QString &staffNumber, const QString &note);

private slots:
    void btnBackClicked();

private:
    QLabel *lblViewName;
    QLabel *lblGender;
    QLabel *lblStaffNumber;
    QLabel *lblNote;

    OptionSelectionControl *oscGender;
    ValueControl *vcAge;
    ValueControl *vcHeight;
    TextLineEdit *txtBxStaffNumber;
    TextEdit *txtBxNote;

    QPushButton *btnBodyMeasurements;

    QPushButton *btnBack;
    QPushButton *btnFeedback;

    const QStringList genderTextValues = QStringList()<<tr("male")<<tr("female");
    const QVector<int> heightValues = QVector<int>()<<150<<160<<170<<180<<190;
    const QVector<int> ageValues = QVector<int>()<<20<<30<<40<<50<<60;
};

#endif // EMPLOYEEVIEW_H
