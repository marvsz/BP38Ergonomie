#ifndef DATELINEEDIT_H
#define DATELINEEDIT_H

#include "textlineedit.h"
#include <QDate>
#include <QRegularExpression>

class DateLineEdit : public TextLineEdit
{
    Q_OBJECT
public:
    explicit DateLineEdit(QWidget *parent = 0);

    QDate getDate() const;
    void setDate(const QDate &date);

signals:
    void dateChanged();

public slots:
    void increaseDay();
    void increaseMonth();
    void increaseYear();
    void decreaseDay();
    void decreaseMonth();
    void decreaseYear();

private slots:
    void updateText();
    void updateDate();

private:
    static const QRegularExpression regEx;

    QDate currentDate;

};

#endif // DATELINEEDIT_H
