#ifndef WORKPLACEVIEW_H
#define WORKPLACEVIEW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QList>
#include "timelineedit.h"
#include "detailedlistitem.h"
#include "numberlineedit.h"
#include "../navigation/simplenavigateablewidget.h"

class WorkplaceView : public SimpleNavigateableWidget
{
    Q_OBJECT
public:
    explicit WorkplaceView(QWidget *parent = 0);
    explicit WorkplaceView(int id, QWidget *parent = 0);

    bool hasAdditionalNavigation() const{
        return true;
    }

    QList<QAbstractButton*> * getAdditionalNavigation() const;

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
    void show(ViewType type);

public slots:

    void setName(const QString &name);
    void setDescription(const QString &description);
    void setCode(const QString &code);
    void setWomanPercentage(int womenPercentage);

    void setBasicTime(const QTime &basic);
    void setSetupTime(const QTime &setup);
    void setRestTime(const QTime &rest);
    void setAllowanceTime(const QTime &allowance);
    void setCycleTime(const QTime &cycle);

    void setLine(const QString &name, const QString &description);
    void setComment(const QString &problemName, const QString &measureName);

private slots:
    void showEmployeeView();
    void btnLineClicked();
    void btnActivityClicked();
    void btnCommentClicked();
    void btnEmployeeClicked();

private:
    int id;

    QPushButton *btnEmployees;

    QLabel *lblName;
    QLabel *lblDescription;
    QLabel *lblCode;
    QLabel *lblPercentageWoman;

    TextLineEdit *txtBxName;
    TextLineEdit *txtBxDescription;
    TextLineEdit *txtBxCode;
    NumberLineEdit *numBxWomanPercentage;

    QLabel* lblGuidelineTimes;
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

    DetailedListItem *line;
    DetailedListItem *activity;
    DetailedListItem *comment;
    DetailedListItem *employee;

    QList<DetailedListItem*> *additions;
};

#endif // WORKPLACEVIEW_H
