#ifndef WORKPROCESSMETADATAVIEW_H
#define WORKPROCESSMETADATAVIEW_H

#include <QWidget>
#include <QLabel>
#include "numberlineedit.h"
#include "valuecontrol.h"
#include "optionselectioncontrol.h"

class WorkProcessMetaDataView : public QWidget
{
    Q_OBJECT
public:
    explicit WorkProcessMetaDataView(QWidget *parent = 0);
    ~WorkProcessMetaDataView();

    QString getDescription() const;
    QString getMTMCode() const;
    int getWorkingHeight() const;
    int getDistance() const;
    int getImpulseIntensity() const;
    int getImpulseCount() const;

signals:

public slots:
    void setWorkProcessMetaData(const QString &desc, const QString &mtmCode, int workingHeight, int distance, int impulseIntensity, int impulseCount);

private:
    QLabel *lblDescription;
    QLabel *lblWorkingHeight;
    QLabel *lblDistance;
    QLabel *lblImpulseIntensity;
    QLabel *lblImpulseCount;

    TextLineEdit *txtBxDescription;
    ValueControl *vcMTMCode;
    NumberLineEdit *numBxWorkingHeight;
    NumberLineEdit *numBxDistance;
    OptionSelectionControl *oscImpulseIntensity;
    NumberLineEdit *numBxImpulseCount;

    static const QVector<QString> MTM_CODE_TEXTS;
    static const QVector<QString> MTM_CODE_VALUES;
    static const QStringList IMPULSE_INTENSITY_TEXTS;
    static const QVector<QVariant> IMPULSE_INTENSITY_VALUES;
};

#endif // WORKPROCESSMETADATAVIEW_H
