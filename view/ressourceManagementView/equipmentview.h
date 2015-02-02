#ifndef EQUIPMENTVIEW_H
#define EQUIPMENTVIEW_H

#include <QWidget>
#include <QLabel>
#include <QScrollArea>
#include <QPushButton>
#include <QVBoxLayout>
#include "textlineedit.h"
#include "numberlineedit.h"
#include "../navigation/simplenavigateablewidget.h"

class EquipmentView : public SimpleNavigateableWidget
{
    Q_OBJECT
public:
    explicit EquipmentView(QWidget *parent = 0);
    ~EquipmentView();

    QString getName() const;
    int getRecoilCount() const;
    int getRecoilIntensity() const;
    int getVibrationCount() const;
    int getVibrationIntensity() const;

signals:
    void saveEquipment();
    void deleteEquipment(int id);

public slots:
    void setEquipment(const QString &name, int recoilCount, int recoilIntensity, int vibrationCount, int vibrationIntensity);
    void addEquipment(int id, const QString &name, int recoilCount, int recoilIntensity, int vibrationCount, int vibrationIntensity);
    void clear();

private slots:
    void btnAddClicked();

private:
    const QList<QStringList> equipmentItemScheme = QList<QStringList>() << (QStringList() << tr("recoil count") << tr ("recoil intensity")) << (QStringList() << tr("vibration count") << tr("vibration intensity"));

    QScrollArea *scEquipment;
    QLabel *lblAddEquipment;
    QLabel *lblName;
    QLabel *lblRecoilCount;
    QLabel *lblRecoilIntensity;
    QLabel *lblVibrationCount;
    QLabel *lblVibrationIntensity;

    TextLineEdit *txtBxName;
    NumberLineEdit *numBxRecoilCount;
    NumberLineEdit *numBxRecoilIntensity;
    NumberLineEdit *numBxVibrationCount;
    NumberLineEdit *numBxVibrationIntensity;

    QPushButton *btnAdd;

    QVBoxLayout *equipmentListLayout;

};

#endif // EQUIPMENTVIEW_H
