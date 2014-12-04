#ifndef TOOL_H
#define TOOL_H

#include <QString>
#include "selectablevaluebutton.h"

class Tool : public SelectableValueButton
{
    Q_OBJECT
public:
    explicit Tool(QString text = "", QVector<bool> options = QVector<bool>(), QWidget *parent = 0);

    bool getOption(int index);
    void setOption(int index, bool b);
    void setName(QString name);

signals:

public slots:

private:
    static int idCounter;
    QString name;
    QVector<bool> options;
};

#endif // TOOL_H
