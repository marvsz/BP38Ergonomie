#ifndef ACTIONFORCEVIEW_H
#define ACTIONFORCEVIEW_H

#include <QMainWindow>
#include <QScrollArea>
#include <QVector>
#include <QString>
#include "valuecontrol.h"

class ActionForceView : public QMainWindow
{
    Q_OBJECT
public:
    explicit ActionForceView(QWidget *parent = 0);

signals:

public slots:

private:
    QWidget*wdgtMainContent;
    QScrollArea* scMainContent;
    QVBoxLayout* lytMainContent;

    const QVector<QString> textsOrgan = QVector<QString>()<<"Finger"<<"Hand"<<"Arm"<<"Fuß/Bein"<<"Ganzkörper";
    const QVector<QString> textsUsedHand = QVector<QString>()<<"Beide"<<"Rechts"<<"Links";
    const QVector<QString> textsDirection = QVector<QString>()<<"Oben"<<"Unten"<<"Vorne"<<"Hinten"<<"Rechts"<<"Links";
    const QVector<QString> textsDirectionValues = QVector<QString>()<<"+A"<<"-A"<<"+B"<<"-B"<<"+C"<<"-C";
    const QVector<int> valuesIntensity = QVector<int>()<<5<<20<<50<<100<<150;

    ValueControl* valConIntensity;
    ValueControl* valConDirection;
    ValueControl* valConOrgan;
    ValueControl* valConUsedHand;

};

#endif // ACTIONFORCEVIEW_H
