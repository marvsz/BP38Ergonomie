
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
#include "../interfaces/ishift.h"
#include "../optionselectioncontrol.h"
#include "../timespinner.h"
#include "../numberlineedit.h"
#include "../detailedlistitem.h"
#include "shiftcalendar.h"
#include "../navigation/simplenavigateablewidget.h"

class ShiftView : public SimpleNavigateableWidget, IShift
{
    Q_OBJECT
    Q_INTERFACES(IShift)
public:
    explicit ShiftView(QWidget *parent = 0);
    ~ShiftView();

    bool hasAdditionalNavigation() const {
        return true;
    }

    QList<QAbstractButton*> * getAdditionalNavigation() const;

    int getShiftType() const;
    QTime getStartTime() const;
    QTime getEndTime() const;

signals:
    void saveShift(QHash<QString, QVariant> values);

    void shiftTypeChanged(int type);
    void beginTimeChanged(QTime begin);
    void endTimeChanged(QTime end);

public slots:
    void setShift(QHash<QString, QVariant> values);

    void setShiftType(int type);
    void setStartTime(const QTime &time);
    void setEndTime(const QTime &time);

private slots:
    void updateShiftTimes(int type);

    void btnRotationClicked();
    void btnEmployeeClicked();
    void btnCalendarClicked();
    void dliEmployeeSelectionClicked();

private:
    int id;
    OptionSelectionControl *oscShiftType;
    TimeSpinner *tsStart;
    TimeSpinner *tsEnd;

    QLabel *lblShiftData;
    QLabel *lblShiftType;
    QLabel *lblShiftTimes;
    QLabel *lblStart;
    QLabel *lblEnd;
    QLabel *lblEmployee;
    DetailedListItem *dliEmployeeSelection;
    QPushButton *btnRotation;
    QPushButton *btnEmployee;
    QPushButton *btnCalendar;

    const QStringList SHIFT_TEXTS = QStringList()<<(tr("early shift"))<<(tr("late shift"))<<(tr("night shift"))<<(tr("special shift"));
};

#endif // SHIFTVIEW_H
