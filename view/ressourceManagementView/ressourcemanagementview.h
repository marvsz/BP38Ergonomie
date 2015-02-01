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
    bool canGoForward() const{
        return false;
    }

private slots:
    void btnEquipmentClicked();
    void btnProductClicked();
    void btnTransportationClicked();

private:
    QPushButton *btnEquipmentView;
    QPushButton *btnProductView;
    QPushButton *btnTransportationView;

};

#endif // RESSOURCEMANAGEMENTVIEW_H
