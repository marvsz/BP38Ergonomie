#ifndef RESSOURCEMANAGEMENTVIEW_H
#define RESSOURCEMANAGEMENTVIEW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

class RessourceManagementView : public QWidget
{
    Q_OBJECT
public:
    explicit RessourceManagementView(QWidget *parent = 0);

signals:
    void back();
    void showEquipmentView();
    void showProductView();
    void showTransportationView();
    void showEmployeeView();
    void showBodyMeasurementsView();

private:
    QLabel *lblViewName;
    QPushButton *btnBack;
    QPushButton *btnEquipmentView;
    QPushButton *btnProductView;
    QPushButton *btnTransportationView;
    QPushButton *btnEmployeeView;


};

#endif // RESSOURCEMANAGEMENTVIEW_H
