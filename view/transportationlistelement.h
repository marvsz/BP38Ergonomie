#ifndef TRANSPORTATIONLISTELEMENT_H
#define TRANSPORTATIONLISTELEMENT_H

#include <QString>
#include "selectablevaluebutton.h"

class TransportationListElement : public SelectableValueButton
{
    Q_OBJECT
public:
    explicit TransportationListElement(QString text = "", QVector<bool> options = QVector<bool>(), int weight = 0, int maxLoad = 0, QWidget *parent = 0);

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

#endif // TRANSPORTATIONLISTELEMENT_H
