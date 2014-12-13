#ifndef TRANSPORTVIEW_H
#define TRANSPORTVIEW_H

#include <QLabel>
#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QGroupBox>
#include "valuecontrol.h"
#include "transportationlistcontrol.h"
#include "anglecontrol.h"
#include "variantspecification.h"
#include "variant.h"
#include "subvariant.h"

namespace Ui {
class TransportView;
}

class TransportView : public QMainWindow
{
    Q_OBJECT

public:
    explicit TransportView(QWidget *parent = 0);
    ~TransportView();

signals:

private slots:
    void typeChanged(QString);

private:
    ValueControl *type;
    ValueControl *last;
    ValueControl *weg;
    ValueControl *hand;
    QWidget *main;
    QWidget *control;
    TransportationListControl *tools;
    QVector<int>* lastValues;
    QVector<int>* heavyLastValues;
};

#endif // TransportView_H
