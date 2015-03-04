#ifndef RESETPOPUP_H
#define RESETPOPUP_H

#include "../navigation/abstractpopupwidget.h"
#include "../detailedlistitem.h"

class ResetPopUp : public AbstractPopUpWidget
{
    Q_OBJECT
public:
    explicit ResetPopUp(QWidget *parent = 0);
    ~ResetPopUp();

    bool headDataSelected() const;
    bool workplacesSelected() const;
    bool equipmentSelected() const;
    bool productsSelected() const;
    bool transportationSelected() const;
    bool employeeSelected() const;
    bool shiftDataSelected() const;

public slots:
    void onEnter();

private slots:
    void headDataClicked();
    void workplacesClicked();
    void equipmentClicked();
    void productsClicked();
    void transportationClicked();
    void employeeClicked();
    void shiftDataClicked();

private:
    DetailedListItem *headData;
    DetailedListItem *workplaces;
    DetailedListItem *equipment;
    DetailedListItem *products;
    DetailedListItem *transportation;
    DetailedListItem *employee;
    DetailedListItem *shiftData;

    bool bHeadData;
    bool bWorklpaces;
    bool bEquipment;
    bool bProducts;
    bool bTransportation;
    bool bEmployee;
    bool bShiftData;
};

#endif // RESETPOPUP_H
