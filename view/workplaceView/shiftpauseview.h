#ifndef SHIFTPAUSEVIEW_H
#define SHIFTPAUSEVIEW_H

#include <QWidget>
#include <QString>
#include <QVector>
#include <QPushButton>
#include "optionselectioncontrol.h"
#include <QLabel>
#include "timelineedit.h"
#include "numberlineedit.h"

class ShiftPauseView : public QWidget
{
    Q_OBJECT

public:
    explicit ShiftPauseView(QWidget *parent = 0);

    QDateTime getShiftBegin() const;
    QDateTime getShiftEnd() const;
    QDateTime getCycleTime() const;
    int getQuantity() const;

    QDateTime getSetupTime() const;
    QDateTime getBasicTime() const;
    QDateTime getRestTime() const;
    QDateTime getAllowanceTime() const;

    QDateTime getBreakBegin() const;
    QDateTime getBreakEnd() const;



public slots:
   void setShift(const QString &shiftType, const QString &shiftBegin, const QString &shiftEnd);
   void setBreak(const QString &breakBegin, const QString &breakEnd);
   void setWorkplaceTimes(const QString &basicTime, const QString &setupTime, const QString &restTime, const QString &allowanceTime, const QString &cycleTime);

signals:
    void back();

private slots:
    void backButtonClicked();

private:
    QPushButton* btnBack;
    QLabel* lblViewDescription;

    QLabel* lblShift;
    QLabel* lblShiftType;
    QLabel* lblCycleTime;
    QLabel* lblShiftBegin;
    QLabel* lblShiftEnd;
    QLabel* lblQuantity;

    const QVector<QString> vecShiftType = QVector<QString>()<<"Frühschicht"<<"Spätschicht"<<"Nachtschicht"<<"Sonderschicht";
    OptionSelectionControl* conShiftType;
    TimeLineEdit* timeCycleTime;
    TimeLineEdit* timeShiftBegin;
    TimeLineEdit* timeShiftEnd;
    NumberLineEdit* txtQuantity;

    QLabel* lblAllowedTime;
    QLabel* lblSetupTime;
    QLabel* lblBasicTime;
    QLabel* lblRestTime;
    QLabel* lblAllowanceTime;

    TimeLineEdit* timeSetupTime;
    TimeLineEdit* timeBasicTime;
    TimeLineEdit* timeRestTime;
    TimeLineEdit* timeAllowanceTime;

    QLabel* lblBreaks;
    QLabel* lblShortBreaks;
    QLabel* lblShortBreaksBegin;
    QLabel* lblShortBreaksEnd;

    const QVector<QString> vecShortBreaks = QVector<QString>()<<"Jederzeit möglich"<<"Bedingt möglich"<<"Führt zu Prozessunterbrechung";
    OptionSelectionControl* conShortBreaks;
    TimeLineEdit* timeBreakBegin;
    TimeLineEdit* timeBreakEnd;
    QPushButton* btnBreakAdd;
    QPushButton* btnBreakRemove;

};

#endif // SHIFTPAUSEVIEW_H
