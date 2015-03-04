#ifndef WORKPLACEPOPUP_H
#define WORKPLACEPOPUP_H

#include "view/navigation/abstractpopupwidget.h"
#include <QLabel>
#include "view/textlineedit.h"
#include "view/numberlineedit.h"
#include "view/timelineedit.h"

class WorkplacePopUp : public AbstractPopUpWidget
{
    Q_OBJECT
public:
    explicit WorkplacePopUp(QWidget *parent = 0);
    ~WorkplacePopUp();

    QString getName() const;
    QString getDescription() const;
    QString getCode() const;
    int getWomanPercentage() const;

    QTime getBasicTime() const;
    QTime getSetupTime() const;
    QTime getRestTime() const;
    QTime getAllowanceTime() const;
    QTime getCycleTime() const;

signals:

public slots:
    void onEnter();

    void setName(const QString &name);
    void setDescription(const QString &description);
    void setCode(const QString &code);
    void setWomanPercentage(int womenPercentage);

    void setBasicTime(const QTime &basic);
    void setSetupTime(const QTime &setup);
    void setRestTime(const QTime &rest);
    void setAllowanceTime(const QTime &allowance);
    void setCycleTime(const QTime &cycle);

private slots:

private:
    QLabel *lblName;
    QLabel *lblDescription;
    QLabel *lblCode;
    QLabel *lblPercentageWomen;

    TextLineEdit *txtBxName;
    TextLineEdit *txtBxDescription;
    TextLineEdit *txtBxCode;
    NumberLineEdit *numBxPercentageWomen;


    QLabel *lblGuidelineTimes;
    QLabel* lblAllowedTime;
    QLabel* lblSetupTime;
    QLabel* lblBasicTime;
    QLabel* lblRestTime;
    QLabel* lblAllowanceTime;
    QLabel* lblCycleTime;

    TimeLineEdit* timeSetupTime;
    TimeLineEdit* timeBasicTime;
    TimeLineEdit* timeRestTime;
    TimeLineEdit* timeAllowanceTime;
    TimeLineEdit* timeCycleTime;
};

#endif // WORKPLACEPOPUP_H
