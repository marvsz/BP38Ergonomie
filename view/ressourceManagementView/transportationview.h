#ifndef TRANSPORTATIONVIEW_H
#define TRANSPORTATIONVIEW_H

#include <QWidget>
#include <QLabel>
#include <QScrollArea>
#include <QVBoxLayout>
#include "optionselectioncontrol.h"
#include "textlineedit.h"
#include "numberlineedit.h"
#include "../navigation/simplenavigateablewidget.h"

class TransportationView : public SimpleNavigateableWidget
{
    Q_OBJECT
public:
    explicit TransportationView(QWidget *parent = 0);
    ~TransportationView();

    bool canGoForward() const{
        return false;
    }

    QString getName() const;
    int getWeight() const;
    int getMaxLoad() const;
    bool hasFixedRoller() const;
    bool hasBrakes() const;

signals:
    void saveTransportation();
    void deleteTransportation(int id);

public slots:
    void setWeight(int weight);
    void setMaxLoad(int maxLoad);
    void setFixedRoller(QVariant value);
    void setBrakes(QVariant value);

    void addTransportation(int id, const QString &name, int weight, int maxLoad, bool fixedRollers, bool brakes);
    void clear();

private slots:
    void btnAddClicked();

private:

    QScrollArea *scTransportation;
    QLabel *lblAddTransportation;
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

    QPushButton *btnAdd;

    QVBoxLayout *transportationListLayout;

    const QList<QStringList> transportationItemScheme = QList<QStringList>() << (QStringList() << tr("empty weight:") << tr("max. load:")) << (QStringList() << tr("fixed rollers:") << tr("brakes:"));
    const QStringList YES_NO_TEXTS = QStringList()<<tr("yes")<<tr("no");
    static const QVector<QVariant> YES_NO_VALUE;

};

#endif // TRANSPORTATIONVIEW_H
