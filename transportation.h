#ifndef TRANSPORTATION_H
#define TRANSPORTATION_H

#include <QString>
#include "selectablevaluebutton.h"

class Transportation : public SelectableValueButton
{
    Q_OBJECT
public:
    explicit Transportation(QString text = "", QVector<bool> options = QVector<bool>(), int weight = 0, QWidget *parent = 0);

    bool getOption(int index);
    void setOption(int index, bool b);
    void setName(QString name);
    int getWeight();
    void setWeight(int weight);
    int getMaxLoad();
    void setMaxLoad(int maxLoad);

signals:

public slots:

private:
    static int idCounter;

    QString name;
    QVector<bool> options;
    int weight;
    int maxLoad;
};

#endif // TRANSPORTATION_H
