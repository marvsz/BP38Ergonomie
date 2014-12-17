#ifndef TRANSPORTATIONLISTCONTROL_H
#define TRANSPORTATIONLISTCONTROL_H

#include <QWidget>
#include <QVector>
#include <QLabel>
#include <QList>
#include <QString>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "transportationlistelement.h"
#include "selectablevaluebutton.h"
#include "valuecontrol.h"

/**
 * @brief A Class providing functionality for displaying and handling different TransportationListElement.
 * TransportationListElement can be add and deleted over buttons. Each transportation
 * has a name and multiple boolean options which can be adjusted over buttons.
 * Furthermore a transportation holds two values for weight and max load of the
 * transportation. These values can be adjusted with two ValueControl.
 */
class TransportationListControl : public QWidget
{
    Q_OBJECT
public:
    explicit TransportationListControl(QVector<QString> *optionNames = NULL, QWidget *parent = 0);

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

    QList<TransportationListElement*>* transportations;
    QLineEdit *newNameEdit;
    QVector<QLabel*> *options;
    ValueControl *transportationWeight;
    ValueControl *transportationMaxLoad;
    QVector<SelectableValueButton*>* optionsTrueBtns;
    QVector<SelectableValueButton*>* optionsFalseBtns;
    QPushButton *addBtn;
    QPushButton *remBtn;

    QGridLayout *mainLayout;
    QHBoxLayout *buttonLayout;
    QVBoxLayout *listLayout;

    TransportationListElement* transportationWithId(int id);
    int transportationIndex(int transportationId);
};

#endif // TRANSPORTATIONLISTCONTROL_H
