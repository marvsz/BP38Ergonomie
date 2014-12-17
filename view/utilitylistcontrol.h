#ifndef UTILITYLISTCONTROL_H
#define UTILITYLISTCONTROL_H

#include <QWidget>
#include <QList>
#include <QSize>
#include <QVector>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QPushButton>

#include <QLineEdit>
#include "utilitylistelement.h"
#include "numberlineedit.h"

/**
 * @brief A Class providing functionality for displaying and handling different UtilityListElement.
 * UtilityListElement can be add and deleted over buttons. Each utility
 * has a name and multiple UtilityOption to adjust the current recoil and vibration values.
 */
class UtilityListControl : public QWidget
{
    Q_OBJECT
public:
    explicit UtilityListControl(QWidget *parent = 0);

signals:

public slots:

private slots:
    void setCurrentUtilityId(int id);
    void disableSelection();
    void addUtility();
    void removeUtility();

    void utilityChanged(int id);

    void recoilIntensityChanged(QString rI);
    void recoilCountChanged(QString rC);
    void vibrationIntensityChanged(QString vI);
    void vibrationCountChanged(QString vC);

private:
    int currentUtilityId;

    QList<UtilityListElement*>* utilites;
    QPushButton *addBtn;
    QPushButton *remBtn;

    QString currentName;
    int currentRecoilIntensity;
    int currentRecoilCount;
    int currentVibrationIntensity;
    int currentVibrationCount;

    QLineEdit* utilityName;
    NumberLineEdit* recoilIntensity;
    NumberLineEdit* recoilCount;
    NumberLineEdit* vibrationIntensity;
    NumberLineEdit* vibrationCount;
    
    QGridLayout *mainLayout;
    QVBoxLayout *listLayout;
    QFormLayout *optionLayout;
    QHBoxLayout *buttonLayout;

    UtilityListElement* utilityWithId(int id);
    int utilityIndex(int utilityId);
    void clearValues();
};

#endif // UTILITYLISTCONTROL_H
