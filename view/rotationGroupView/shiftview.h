
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
#include "../timelineedit.h"
#include "numberlineedit.h"
#include "detailedlistitem.h"
#include "shiftcalendar.h"

class ShiftView : public QWidget
{
    Q_OBJECT
public:
    explicit ShiftView(QWidget *parent = 0);

    QString getType() const;
    QTime getStartTime() const;
    QTime getEndTime() const;

signals:
    void back();

public slots:
    void setStartTime(const QTime &time);
    void setEndTime(const QTime &time);

private slots:
    void updateCalendarStart();
    void updateCalendarEnd();
    void updateShiftTimes(int type);

private:
    int id;
    OptionSelectionControl *oscShiftType;
    TimeLineEdit *timeBxStart;
    TimeLineEdit *timeBxEnd;

    QLabel *lblShiftData;
    QLabel *lblShiftType;
    QLabel *lblStart;
    QLabel *lblEnd;
    QLabel *lblEmployee;
    QPushButton *btnChooseEmployee;
    DetailedListItem *dliEmployee;
    QLabel *lblAddBreak;
    QLabel *lblBreakDuration;
    NumberLineEdit *numBxBreakDuration;
    QPushButton *btnAddBreak;
    QLabel *lblAddRotationGroup;
    QWidget *rotationGroupListContent;
    QScrollArea *scRotationGroups;
    QVBoxLayout *rotationGroupListLayout;
    QPushButton *btnMoreRotationGroups;
    ShiftCalendar *calendar;

    QPushButton *btnBack;
    QLabel *lblViewName;
    QPushButton *btnFeedback;

    const QStringList SHIFT_TEXTS = QStringList()<<(tr("early shift"))<<(tr("late shift"))<<(tr("night shift"))<<(tr("special shift"));
};

#endif // SHIFTVIEW_H
