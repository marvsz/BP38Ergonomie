#ifndef EQUIPMENTPOPUP_H
#define EQUIPMENTPOPUP_H

#include "../navigation/abstractpopupwidget.h"
#include "../numberlineedit.h"

class EquipmentPopUp : public AbstractPopUpWidget
{
    Q_OBJECT
public:
    explicit EquipmentPopUp(QWidget *parent = 0);
    ~EquipmentPopUp();

    QString getName() const;
    int getRecoilCount() const;
    int getRecoilIntensity() const;
    int getVibrationCount() const;
    int getVibrationIntensity() const;

public slots:
    void onEnter();

private:
    TextLineEdit *txtBxName;
    NumberLineEdit *numBxRecoilCount;
    NumberLineEdit *numBxRecoilIntensity;
    NumberLineEdit *numBxVibrationCount;
    NumberLineEdit *numBxVibrationIntensity;

};

#endif // EQUIPMENTPOPUP_H
