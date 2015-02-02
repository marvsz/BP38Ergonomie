#ifndef RESSOURCEMANAGEMENTVIEW_H
#define RESSOURCEMANAGEMENTVIEW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include "../navigation/simplenavigateablewidget.h"

class RessourceManagementView : public SimpleNavigateableWidget
{
    Q_OBJECT
public:
    explicit RessourceManagementView(QWidget *parent = 0);

private slots:
    void btnEquipmentClicked();
    void btnProductClicked();
    void btnTransportationClicked();
    void btnEmployeeClicked();
    
private:
    QPushButton *btnEquipmentView;
    QPushButton *btnProductView;
    QPushButton *btnTransportationView;
    QPushButton *btnEmployeeView;


};

#endif // RESSOURCEMANAGEMENTVIEW_H
