#ifndef SHIFTANDPAUSEDATA_H
#define SHIFTANDPAUSEDATA_H

#include <QWidget>
#include <QString>
#include <QVector>
#include <QPushButton>
#include "optionselectioncontrol.h"
#include <QLabel>
#include "timelineedit.h"
#include "numberlineedit.h"

class ShiftAndPauseData : public QWidget
{
    Q_OBJECT

public:
    explicit ShiftAndPauseData(QWidget *parent = 0);

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
   /* void setShift();
    void setAllowedTime();
    void setBreak();*/

signals:
    /*void showMetadataView();
    void saveShiftAndPauseData();*/

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

#endif // SHIFTANDPAUSEDATA_H
