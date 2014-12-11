#ifndef TRANSPORTATIONLISTCONTROL_H
#define TRANSPORTATIONLISTCONTROL_H

#include <QGroupBox>
#include <QVector>
#include <QLabel>
#include <QList>
#include <QString>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "transportationlistelement.h"
#include "selectablevaluebutton.h"
#include "valuecontrol.h"

class TransportationListControl : public QGroupBox
{
    Q_OBJECT
public:
    explicit TransportationListControl(QString name = "", QVector<QString> *optionNames = NULL, QWidget *parent = 0);

signals:

public slots:

private slots:
    void setCurrentTransportationId(int id);
    void optionTruePressed(int index);
    void optionFalsePressed(int index);
    void optionChanged(int index);
    void transportationChanged(int id);
    void addTransportation();
    void removeTransportation();
    void disableSelection();
    void weightChanged(int newWeight);
    void maxLoadChanged(int newWeight);

private:
    int currentTransportationId;
    QVector<bool> currentOptions;
    int currentWeight;
    int currentMaxLoad;

    QLabel *name;
    QList<TransportationListElement*>* transportations;
    QLabel *newName;
    QLineEdit *newNameEdit;
    QVector<QLabel*> *options;
    ValueControl *transportationWeight;
    ValueControl *transportationMaxLoad;
    QVector<SelectableValueButton*>* optionsTrueBtns;
    QVector<SelectableValueButton*>* optionsFalseBtns;
    SelectableValueButton *addBtn;
    SelectableValueButton *remBtn;
    bool isOptionChosen();
    TransportationListElement* transportationWithId(int id);
    int transportationIndex(int transportationId);
    QVBoxLayout *listLayout;
};

#endif // TRANSPORTATIONLISTCONTROL_H
