#ifndef UTILITYLISTCONTROL_H
#define UTILITYLISTCONTROL_H

#include <QGroupBox>
#include <QList>
#include <QVector>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include "utilitylistelement.h"
#include "utilityoption.h"
#include "selectablevaluebutton.h"

class UtilityListControl : public QGroupBox
{
    Q_OBJECT
public:
    explicit UtilityListControl(QString name = "", QWidget *parent = 0);

signals:

public slots:

private slots:
    void setCurrentUtilityId(int id);
    void disableSelection();
    void addUtility();
    void removeUtility();

    void utilityChanged(int id);

    void recoilIntensityChanged(int rI);
    void recoilCountChanged(int rC);
    void vibrationIntensityChanged(int vI);
    void vibrationCountChanged(int vC);

private:
    int currentUtilityId;

    QLabel* nameLabel;
    QList<UtilityListElement*>* utilites;
    SelectableValueButton *addBtn;
    SelectableValueButton *remBtn;

    QString currentName;
    int currentRecoilIntensity;
    int currentRecoilCount;
    int currentVibrationIntensity;
    int currentVibrationCount;

    UtilityOption* utilityName;
    UtilityOption* recoilIntensity;
    UtilityOption* recoilCount;
    UtilityOption* vibrationIntensity;
    UtilityOption* vibrationCount;
    
    QVBoxLayout *mainLayout;
    QVBoxLayout *listLayout;
    QFormLayout *optionLayout;
    QHBoxLayout *buttonLayout;

    UtilityListElement* utilityWithId(int id);
    int utilityIndex(int utilityId);
    void clearValues();


};

#endif // UTILITYLISTCONTROL_H
