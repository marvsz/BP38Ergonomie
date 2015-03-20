#ifndef SHIFTCALENDAR_H
#define SHIFTCALENDAR_H

#include <QTime>
#include <QScrollArea>
#include <QPainter>
#include <QPicture>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "../interfaces/icalendarlist.h"
#include "../interfaces/icalendar.h"
#include "../interfaces/irotationgrouptasklist.h"
#include "../selectablevaluebutton.h"
#include "../numberlineedit.h"
#include "../textlineedit.h"
#include "../navigation/simplenavigateablewidget.h"

class ShiftCalendar : public SimpleNavigateableWidget, ICalendarList, ICalendar, IRotationGroupTaskList
{
    Q_OBJECT
    Q_INTERFACES(IRotationGroupTaskList)
    Q_INTERFACES(ICalendarList)
    Q_INTERFACES(ICalendar)

public:
    explicit ShiftCalendar(QWidget *parent = 0, const QTime &beginTime = QTime(6,0), const QTime &endTime = QTime(14, 0));
    ~ShiftCalendar();

    bool hasAdditionalNavigation() const {
        return true;
    }

    QList<QAbstractButton*> * getAdditionalNavigation() const;

    QString getBreakName() const;
    int getBreakDuration() const;

signals:
    void createRotationGroupTask(QHash<QString, QVariant> values);
    void deleteRotationGroupTask(int id);
    void selectRotationGroupTask(int id);

    void createCalendarRotationGroup(QHash<QString, QVariant> values);
    void deleteCalendarRotationGroup(int id);
    void createCalendarBreak(QHash<QString, QVariant> values);
    void deleteCalendarBreak(int id);

    void moveEntryUp(int id);
    void moveEntryDown(int id);

public slots:
    void addRotationGroupTask(QHash<QString, QVariant> values);
    void updateRotationGroupTask(QHash<QString, QVariant> values);
    void removeRotationGroupTask(int id);
    void clearRotationGroupTasks();

    void addCalendarRotationGroup(QHash<QString, QVariant> values);
    void updateCalendarRotationGroup(QHash<QString, QVariant> values);
    void removeCalendarRotationGroup(int id);
    void addCalendarBreak(QHash<QString, QVariant> values);
    void updateCalendarBreak(QHash<QString, QVariant> values);
    void removeCalendarBreak(int id);
    void clearCalendar();
    void setTimes(QHash<QString, QVariant> values);

private slots:
    void btnAddBreakClicked();
    void btnRotationClicked();
    void setSelectedId(int id);

    void btnMoveUpClicked();
    void btnMoveDownClicked();
    void btnDeleteClicked();

private:
    static const int HOUR_HEIGHT = 80;

    QTime beginTime;
    QTime endTime;

    QPushButton *btnRotation;

    QLabel *lblAddRotationGroup;
    QWidget *rotationGroupListContent;
    QScrollArea *scRotationGroups;
    QVBoxLayout *rotationGroupListLayout;

    QLabel *lblAddBreak;
    QLabel *lblBreakDuration;
    NumberLineEdit *numBxBreakDuration;
    QPushButton *btnAddBreak;
    int currentId;

    QPainter painter;
    QPicture picCalendar;
    QLabel *lblCalendar;
    QScrollArea *scCalendar;
    QVBoxLayout *calendarEntryLayout;    
    QPushButton *btnMoveUp;
    QPushButton *btnMoveDown;
    QPushButton *btnDelete;

    void drawBackground();

    const QList<QStringList> rotationGroupCaptions = QList<QStringList>() << (QStringList() << tr("Duration"));

};

#endif // SHIFTCALENDAR_H
