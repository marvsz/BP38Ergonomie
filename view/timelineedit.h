#ifndef TIMELINEEDIT_H
#define TIMELINEEDIT_H

#include "textlineedit.h"

class TimeLineEdit : public TextLineEdit
{
    Q_OBJECT
public:
    explicit TimeLineEdit(QWidget *parent =0);

    int getValue() const;
    void setValue(int value);

signals:

public slots:

};

#endif // TIMELINEEDIT_H
