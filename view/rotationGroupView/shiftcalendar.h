#ifndef SHIFTCALENDAR_H
#define SHIFTCALENDAR_H

#include <QTime>
#include <QScrollArea>
#include <QPainter>
#include <QPicture>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "../selectablevaluebutton.h"
#include "../numberlineedit.h"
#include "../textlineedit.h"
#include "view/navigation/simplenavigateablewidget.h"

class ShiftCalendar : public SimpleNavigateableWidget
{
    Q_OBJECT
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

    void createCalendarRotationGroup(int id);
    void createBreak();


public slots:

    void addSelectionRotationGroup(int id, int duration = 60, int workplaces = 1, const QString &name = "");
    void clearSelection();

    void addCalendarRotationGroup(int id, int duration = 60, const QString &name = "Rotationsgruppe");
    void addCalendarBreak(int id, int duration = 60, const QString &name = "Pause");
    void clearCalendar();

    void setBeginTime(const QTime &beginTime);
    void setEndTime(const QTime &endTime);

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
