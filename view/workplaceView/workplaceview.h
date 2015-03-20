#ifndef WORKPLACEVIEW_H
#define WORKPLACEVIEW_H

#include <QLabel>
#include <QPushButton>
#include "../timelineedit.h"
#include "../detailedlistitem.h"
#include "../numberlineedit.h"
#include "../navigation/simplenavigateablewidget.h"
#include "../interfaces/iworkplace.h"
#include "../../databaseHandler/dbconstants.h"

class WorkplaceView : public SimpleNavigateableWidget, IWorkplace
{
    Q_OBJECT
    Q_INTERFACES(IWorkplace)
public:
    explicit WorkplaceView(QWidget *parent = 0);

    bool hasAdditionalNavigation() const{
        return true;
    }

    QList<QAbstractButton*> * getAdditionalNavigation() const;

signals:

    void saveWorkplace(QHash<QString, QVariant> values);


public slots:
    void setWorkplace(QHash<QString, QVariant> values);
    void setSavedLine(QHash<QString, QVariant> values);
    void setSavedComment(QHash<QString, QVariant> values);
    void onLeaving();

private slots:
    void showEmployeeView();
    void btnLineClicked();
    void btnActivityClicked();
    void btnCommentClicked();
    void btnEmployeeClicked();

private:
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
};

#endif // WORKPLACEVIEW_H
