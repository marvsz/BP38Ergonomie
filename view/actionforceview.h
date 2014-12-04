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
    void menuViewSelected();

public slots:
    void openMenuView();

private:
    QWidget*wdgtMainContent;
    QScrollArea* scMainContent;
    QVBoxLayout* lytMainContent;
    QPushButton* btnBack;
    QLabel* lblViewName;

    QVector<QString*> *textsOrgan;
    QVector<QString*> *textsUsedHand;
    QVector<QString*> *textsDirection;
    QVector<int> *valuesIntensity;

    ValueControl* valConIntensity;
    ValueControl* valConDirection;
    ValueControl* valConOrgan;
    ValueControl* valConUsedHand;

};

#endif // ACTIONFORCEVIEW_H
