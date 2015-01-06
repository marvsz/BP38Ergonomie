#ifndef TRANSPORTVIEW_H
#define TRANSPORTVIEW_H

#include <QLabel>
#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QGroupBox>
#include "valuecontrol.h"
#include "transportationlistcontrol.h"

namespace Ui {
class TransportView;
}

/**
 * @brief A class providing a view for transporthandling. The class contains
 * different ValueControl for the type, of handling the weight to be handled,
 * the way to go and the hand used. Furthermore there is a TransportationListControl
 * with the list of transportations available.
 */
class TransportView : public QMainWindow
{
    Q_OBJECT

public:
    explicit TransportView(QWidget *parent = 0);
    ~TransportView();

signals:

private slots:
    /**
     * @brief A slot that is called, whenever the type of handling changes.
     * Depending of the new type the ValueControl ranges of the weight
     * to be handled are adapted.
     * @param type The new type selected.
     */
    void typeChanged(QString type);

private:
    ValueControl *type;
    ValueControl *last;
    ValueControl *weg;
    ValueControl *hand;
    QWidget *main;
    QWidget *control;
    TransportationListControl *tools;

    const QVector<int> lastValues = QVector<int>()<<2<<3<<5<<10<<20;
    const QVector<int> heavyLastValues = QVector<int>()<<100<<500<<1000<<1500<<2000;
    const QVector<int> wegValues = QVector<int>()<<2<<3<<5<<10<<20;
    const QVector<QString> typeValues = QVector<QString>()<<"Halten"<<"Umsetzen"<<"Tragen"<<"Ziehen und Schieben";
    const QVector<QString> handValues = QVector<QString>()<<"Links"<<"Beide"<<"Rechts";
};

#endif // TransportView_H
