#ifndef NUMBERLINEEDIT_H
#define NUMBERLINEEDIT_H

#include "textlineedit.h"

class NumberLineEdit : public TextLineEdit
{
    Q_OBJECT
public:
    explicit NumberLineEdit(QWidget *parent = 0);

    int getValue() const;
    void setValue(int value);

signals:

public slots:

};

#endif // NUMBERLINEEDIT_H
