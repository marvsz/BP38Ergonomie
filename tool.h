#ifndef TOOL_H
#define TOOL_H

#include "textqpushbutton.h"
#include <QString>

class Tool : public TextQPushButton
{
    Q_OBJECT
public:
    explicit Tool(int id = 0, QString text = "", bool opt1 = false, bool opt2 = false, QWidget *parent = 0);

    bool getOpt1();
    bool getOpt2();
    void setOpt1(bool b);
    void setOpt2(bool b);
    void setName(QString name);

signals:

public slots:

private:
    int id;
    QString name;
    bool opt1;
    bool opt2;
};

#endif // TOOL_H
