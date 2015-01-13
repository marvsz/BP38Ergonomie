#ifndef TRANSPORTATIONVIEW_H
#define TRANSPORTATIONVIEW_H

#include <QWidget>
#include <QLabel>
#include <QScrollArea>
#include <QVBoxLayout>
#include "optionselectioncontrol.h"
#include "textlineedit.h"
#include "numberlineedit.h"

class TransportationView : public QWidget
{
    Q_OBJECT
public:
    explicit TransportationView(QWidget *parent = 0);
    ~TransportationView();

    int getWeight() const;
    int getMaxLoad() const;
    QVariant hasFixedRoller() const;
    QVariant hasBrakes() const;

signals:
    void back();
    void saveTransportation();
    void deleteTransportation(int id);

public slots:
    void setWeight(int weight);
    void setMaxLoad(int maxLoad);
    void setFixedRoller(QVariant value);
    void setBrakes(QVariant value);

    void addTransportation(int id, const QString &name, int weight, int maxLoad, const QString &fixedRollers, const QString &brakes);
    void clear();

private slots:
    void btnAddClicked();

private:

    QScrollArea *scTransportation;
    QLabel *lblAddTransportation;
    QLabel *lblViewName;
    QLabel *lblName;
    QLabel *lblWeight;
    QLabel *lblMaxLoad;
    QLabel *lblFixedRoller;
    QLabel *lblBrakes;

    TextLineEdit *txtBxName;
    NumberLineEdit *numBxWeight;
    NumberLineEdit *numBxMaxLoad;
    OptionSelectionControl *oscFixedRoller;
    OptionSelectionControl *oscBrakes;

    QPushButton *btnBack;
    QPushButton *btnAdd;

    QVBoxLayout *transportationListLayout;

    static const QList<QStringList> transportationItemScheme;
    static const QStringList YES_NO_TEXTS;
    static const QVector<QVariant> YES_NO_VALUE;

};

#endif // TRANSPORTATIONVIEW_H
