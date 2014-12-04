#ifndef LISTCONTROL_H
#define LISTCONTROL_H

#include <QGroupBox>
#include <QVector>
#include <QLabel>
#include <QList>
#include <QString>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "transportation.h"
#include "selectablevaluebutton.h"
#include "valuecontrol.h"


class ListControl : public QGroupBox
{
    Q_OBJECT
public:
    explicit ListControl(QString name = "", QVector<QString> *optionNames = NULL, QWidget *parent = 0);

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


private:
    int currentTransportationId;
    QVector<bool> currentOptions;
    QLabel *name;
    QList<Transportation*>* transportations;
    QLabel *newName;
    QLineEdit *newNameEdit;
    QVector<QLabel*> *options;
    ValueControl *transportationWeight;
    QVector<SelectableValueButton*>* optionsTrueBtns;
    QVector<SelectableValueButton*>* optionsFalseBtns;
    SelectableValueButton *addBtn;
    SelectableValueButton *remBtn;
    bool isOptionChosen();
    Transportation* transportationWidthId(int id);
    int transportationIndex(int transportationId);
};

#endif // LISTCONTROL_H
