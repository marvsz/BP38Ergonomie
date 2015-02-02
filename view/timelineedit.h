#ifndef TIMELINEEDIT_H
#define TIMELINEEDIT_H
#include <QTime>
#include "../enum.h"
#include "textlineedit.h"

class TimeLineEdit : public TextLineEdit
{
    Q_OBJECT
public:
    explicit TimeLineEdit(QWidget *parent = 0, TimeLineType type = TimeLineType::MINUTE_SECOND);

    QTime getValue();
    void setValue(const QTime &value);

signals:

public slots:

private:
    TimeLineType type;

    void normalizeText();
};

#endif // TIMELINEEDIT_H
