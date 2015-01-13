#ifndef EQUIPMENTVIEW_H
#define EQUIPMENTVIEW_H

#include <QWidget>
#include <QLabel>
#include <QScrollArea>
#include <QPushButton>
#include <QVBoxLayout>
#include "textlineedit.h"
#include "numberlineedit.h"

class EquipmentView : public QWidget
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
    void back();
    void saveEquipment();
    void deleteEquipment(int id);

public slots:
    void setEquipment(const QString &name, int recoilCount, int recoilIntensity, int vibrationCount, int vibrationIntensity);
    void addEquipment(int id, const QString &name, int recoilCount, int recoilIntensity, int vibrationCount, int vibrationIntensity);
    void clear();

private slots:
    void btnAddClicked();

private:
    static const QList<QStringList> equipmentItemScheme;

    QScrollArea *scEquipment;
    QLabel *lblAddEquipment;
    QLabel *lblViewName;
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

    QPushButton *btnBack;
    QPushButton *btnAdd;

    QVBoxLayout *equipmentListLayout;

};

#endif // EQUIPMENTVIEW_H
