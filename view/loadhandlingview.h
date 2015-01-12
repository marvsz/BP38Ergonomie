#ifndef LOADHANDLINGVIEW_H
#define LOADHANDLINGVIEW_H

#include <QLabel>
#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QGroupBox>
#include "valuecontrol.h"
#include "transportationlistcontrol.h"

/**
 * @brief A class providing a view for transporthandling. The class contains
 * different ValueControl for the type, of handling the weight to be handled,
 * the way to go and the hand used. Furthermore there is a TransportationListControl
 * with the list of transportations available.
 */
class LoadHandlingView : public QWidget
{
    Q_OBJECT

public:
    explicit LoadHandlingView(QWidget *parent = 0);
    ~LoadHandlingView();

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
    const QVector<QString> typeValues = QVector<QString>()<<tr("holding")<<tr("replacing")<<tr("carrying")<<tr("pulling and pushing");
    const QVector<QString> handValues = QVector<QString>()<<tr("left")<<tr("both")<<tr("right");
};

#endif // LoadHandlingView_H
