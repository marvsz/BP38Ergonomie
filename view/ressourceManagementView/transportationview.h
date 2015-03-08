#ifndef TRANSPORTATIONVIEW_H
#define TRANSPORTATIONVIEW_H

#include <QWidget>
#include <QLabel>
#include <QScrollArea>
#include <QVBoxLayout>
#include "../optionselectioncontrol.h"
#include "../textlineedit.h"
#include "../numberlineedit.h"
#include "../navigation/simplenavigateablewidget.h"
#include "../interfaces/itransportationlist.h"
#include "../interfaces/itransportation.h"

class TransportationView : public SimpleNavigateableWidget, ITransportationList
{
    Q_OBJECT
    Q_INTERFACES(ITransportationList)
public:
    explicit TransportationView(QWidget *parent = 0);
    ~TransportationView();

signals:
    void createTransportation(QHash<QString, QVariant> values);
    void deleteTransportation(int id);
    void selectTransportation(int id);

public slots:
    void addTransportation(QHash<QString, QVariant> values);
    void removeTransportation(int id);
    void updateTransportation(QHash<QString, QVariant> values);
    void clearTransportations();

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
