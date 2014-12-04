#ifndef TRANSPORTVIEW_H
#define TRANSPORTVIEW_H

#include <QLabel>
#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include "valuecontrol.h"
#include "listcontrol.h"
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
    explicit TransportView(QString windowName = "", QWidget *parent = 0);
    ~TransportView();

signals:
    void menuViewSelected();

private slots:
    void openMenuView();

private:
    QPushButton *backButton;
    QLabel *label;
    QLabel *lblViewName;

    /*AngleControl *control;
    VariantSpecification *type;
    Variant *var;
    SubVariant *last;
    SubVariant *weg;
    SubVariant *hand;*/

    ValueControl *type;
    ValueControl *last;
    ValueControl *weg;
    ValueControl *hand;
    QWidget *main;
    QWidget *control;
    ListControl *tools;
};

#endif // TransportView_H
