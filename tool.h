#ifndef TOOL_H
#define TOOL_H

#include "textqpushbutton.h"
#include <QString>

class Tool : public TextQPushButton
{
    Q_OBJECT
public:
    explicit Tool(int id = 0, QString text = "", QVector<bool> options = QVector<bool>(), QWidget *parent = 0);

    bool getOption(int index);
    void setOption(int index, bool b);
    void setName(QString name);

signals:

public slots:

private:
    int id;
    QString name;
    QVector<bool> options;
};

#endif // TOOL_H
