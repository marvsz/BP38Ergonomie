#ifndef TIMELINEEDIT_H
#define TIMELINEEDIT_H
#include <QTime>

#include "textlineedit.h"

class TimeLineEdit : public TextLineEdit
{
    Q_OBJECT
public:
    explicit TimeLineEdit(QWidget *parent =0);

    QTime getValue() const;
    void setValue(QTime value);

signals:

public slots:

};

#endif // TIMELINEEDIT_H
