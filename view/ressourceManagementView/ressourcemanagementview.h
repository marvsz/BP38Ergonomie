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

private:
    QLabel *lblViewName;
    QPushButton *btnBack;
    QPushButton *btnEquipmentView;
    QPushButton *btnProductView;
    QPushButton *btnTransportationView;

};

#endif // RESSOURCEMANAGEMENTVIEW_H
