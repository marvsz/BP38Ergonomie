
#ifndef SHIFTVIEW_H
#define SHIFTVIEW_H

#include <QWidget>
#include <QTime>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QScrollArea>
#include "../optionselectioncontrol.h"
#include "../timespinner.h"
#include "../numberlineedit.h"
#include "../detailedlistitem.h"
#include "shiftcalendar.h"
#include "../navigation/simplenavigateablewidget.h"

class ShiftView : public SimpleNavigateableWidget
{
    Q_OBJECT
public:
    explicit ShiftView(QWidget *parent = 0);

    bool hasAdditionalNavigation() const {
        return true;
    }

    QList<QAbstractButton*> * getAdditionalNavigation() const;

    QString getType() const;
    QTime getStartTime() const;
    QTime getEndTime() const;

signals:

public slots:
    void setStartTime(const QTime &time);
    void setEndTime(const QTime &time);

private slots:

    void updateShiftTimes(int type);

    void btnAddBreakClicked();
    void btnEmployeeClicked();
    void btnMoreRotationGroupsClicked();
    void btnCalendarClicked();

private:
    int id;
    OptionSelectionControl *oscShiftType;
    TimeSpinner *tsStart;
    TimeSpinner *tsEnd;

    QLabel *lblShiftData;
    QLabel *lblShiftType;
    QLabel *lblStart;
    QLabel *lblEnd;
    QLabel *lblEmployee;
    QLabel *lblAddBreak;
    QLabel *lblBreakDuration;
    NumberLineEdit *numBxBreakDuration;
    QPushButton *btnAddBreak;
    QLabel *lblAddRotationGroup;
    QWidget *rotationGroupListContent;
    QScrollArea *scRotationGroups;
    QVBoxLayout *rotationGroupListLayout;
    QPushButton *btnMoreRotationGroups;
    QPushButton *btnEmployee;
    QPushButton *btnCalendar;

    const QStringList SHIFT_TEXTS = QStringList()<<(tr("early shift"))<<(tr("late shift"))<<(tr("night shift"))<<(tr("special shift"));
};

#endif // SHIFTVIEW_H
