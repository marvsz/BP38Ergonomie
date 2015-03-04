#ifndef WORKPROCESSBUTTON_H
#define WORKPROCESSBUTTON_H

#include "../selectablevaluebutton.h"
#include <QTime>

class WorkProcessButton : public SelectableValueButton
{
    Q_OBJECT
public:
    explicit WorkProcessButton(int id, int value, const QTime &start, const QTime &end, QWidget *parent = 0);
    ~WorkProcessButton();

    QTime getEndTime() const;
    QTime getStartTime() const;

signals:
    void clickedWithIDValue(int id, int value);


public slots:
    void setEndTime(const QTime &end);
    void setStartTime(const QTime &start);

private slots:
    void btnClicked();

private:
    QTime start;
    QTime end;

};

#endif // WORKPROCESSBUTTON_H
