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

    const QVector<QString> textsOrgan = QVector<QString>()<<tr("finger")<<tr("hand")<<tr("arm")<<tr("foot/leg")<<tr("full body");
    const QVector<QString> textsUsedHand = QVector<QString>()<<tr("both")<<tr("right")<<tr("left");
    const QVector<QString> textsDirection = QVector<QString>()<<tr("above")<<tr("below")<<tr("front")<<tr("back")<<tr("right")<<tr("left");
    const QVector<QString> textsDirectionValues = QVector<QString>()<<tr("+A")<<tr("-A")<<tr("+B")<<tr("-B")<<tr("+C")<<tr("-C");
    const QVector<int> valuesIntensity = QVector<int>()<<5<<20<<50<<100<<150;

    ValueControl* valConIntensity;
    ValueControl* valConDirection;
    ValueControl* valConOrgan;
    ValueControl* valConUsedHand;

};

#endif // ACTIONFORCEVIEW_H
