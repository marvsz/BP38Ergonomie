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

    QTime getShiftBegin() const;
    QTime getShiftEnd() const;
    int getQuantity() const;

    QTime getBreakBegin() const;
    QTime getBreakEnd() const;

public slots:
   void setShift(const QString &shiftType, const QTime &shiftBegin, const QTime &shiftEnd);
   void setBreak(const QTime &breakBegin, const QTime &breakEnd);

signals:
    void back();

private slots:
    void backButtonClicked();

private:
    QPushButton* btnBack;
    QLabel* lblViewDescription;

    QLabel* lblShift;
    QLabel* lblShiftType;
    QLabel* lblShiftBegin;
    QLabel* lblShiftEnd;
    QLabel* lblQuantity;

    const QVector<QString> vecShiftType = QVector<QString>()<<tr("early shift")<<tr("late shift")<<tr("night shift")<<tr("special shift");
    OptionSelectionControl* conShiftType;
    TimeLineEdit* timeShiftBegin;
    TimeLineEdit* timeShiftEnd;
    NumberLineEdit* txtQuantity;

    QLabel* lblBreaks;
    QLabel* lblShortBreaks;
    QLabel* lblShortBreaksBegin;
    QLabel* lblShortBreaksEnd;

    const QVector<QString> vecShortBreaks = QVector<QString>()<<tr("possible everytime")<<tr("possible with constraints")<<tr("leads to process breaks");
    OptionSelectionControl* conShortBreaks;
    TimeLineEdit* timeBreakBegin;
    TimeLineEdit* timeBreakEnd;
    QPushButton* btnBreakAdd;
    QPushButton* btnBreakRemove;

};

#endif // SHIFTPAUSEVIEW_H
