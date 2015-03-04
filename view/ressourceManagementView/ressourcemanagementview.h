#ifndef RESSOURCEMANAGEMENTVIEW_H
#define RESSOURCEMANAGEMENTVIEW_H

#include <QWidget>
#include "../iconbutton.h"
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
    IconButton *btnEquipmentView;
    IconButton *btnProductView;
    IconButton *btnTransportationView;
    IconButton *btnEmployeeView;


};

#endif // RESSOURCEMANAGEMENTVIEW_H
