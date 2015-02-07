#ifndef SHIFTCALENDAR_H
#define SHIFTCALENDAR_H

#include <QWidget>
#include <QTime>
#include <QScrollArea>
#include <QPainter>
#include <QPicture>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "../numberlineedit.h"
#include "../view/navigation/simplenavigateablewidget.h"

class ShiftCalendar : public SimpleNavigateableWidget
{
    Q_OBJECT
public:
    explicit ShiftCalendar(QWidget *parent = 0, const QTime &beginTime = QTime(6,0), const QTime &endTime = QTime(22, 0));
    void setBeginTime(const QTime &beginTime);
    void setEndTime(const QTime &endTime);

signals:

public slots:
    void addRotationGroup(const QString &name, int duration);
    void addBreak(int duration);
    void clear();

private slots:
    void btnAddBreakClicked();

private:
    static const int HOUR_HEIGHT = 80;

    QTime beginTime;
    QTime endTime;

    QLabel *lblAddRotationGroup;
    QWidget *rotationGroupListContent;
    QScrollArea *scRotationGroups;
    QVBoxLayout *rotationGroupListLayout;

    QLabel *lblAddBreak;
    QLabel *lblBreakDuration;
    NumberLineEdit *numBxBreakDuration;
    QPushButton *btnAddBreak;

    QPainter painter;
    QPicture picCalendar;
    QLabel *lblCalendar;
    QScrollArea *scCalendar;
    QVBoxLayout *calendarEntryLayout;

    void drawBackground();
};

#endif // SHIFTCALENDAR_H
