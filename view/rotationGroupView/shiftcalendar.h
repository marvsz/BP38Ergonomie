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
#include "../selectablevaluebutton.h"
#include "../numberlineedit.h"
#include "../textlineedit.h"
#include "../navigation/simplenavigateablewidget.h"

class ShiftCalendar : public SimpleNavigateableWidget, ICalendarList, ICalendar
{
    Q_OBJECT
    Q_INTERFACES(IRotationGroupList)
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
    void createRotationGroup(QHash<QString, QVariant> values);
    void deleteRotationGroup(int id);
    void selectRotationGroup(int id);

    void createCalendarRotationGroup(QHash<QString, QVariant> values);
    void deleteCalendarRotationGroup(int id);
    void selectCalendarRotationGroup(int id);
    void createCalendarBreak(QHash<QString, QVariant> values);
    void deleteCalendarBreak(int id);
    void selectCalendarBreak(int id);

public slots:
    void addRotationGroup(QHash<QString, QVariant> values);
    void updateRotationGroup(QHash<QString, QVariant> values);
    void removeRotationGroup(int id);
    void clearRotationGroups();

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
    QLabel *lblBreakName;
    TextLineEdit *txtBxBreakName;
    QPushButton *btnAddBreak;
    int currentId;

    QPainter painter;
    QPicture picCalendar;
    QLabel *lblCalendar;
    QScrollArea *scCalendar;
    QVBoxLayout *calendarEntryLayout;
    QVector<SelectableValueButton*>* calendarEntries;
    QPushButton *btnMoveUp;
    QPushButton *btnMoveDown;
    QPushButton *btnDelete;

    void drawBackground();

    static const QList<QStringList> rotationGroupCaptions;

};

#endif // SHIFTCALENDAR_H
