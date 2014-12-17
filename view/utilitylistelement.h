#ifndef UTILITYLISTELEMENT_H
#define UTILITYLISTELEMENT_H
#include <QString>
#include "selectablevaluebutton.h"

/**
 * @brief A class providing functionality for a list element of the
 * UtiliyListControl. A UtilityListElement is a SelectableValueButton
 * which has a recoil intensity and count and a vibration intensity and count.
 */
class UtilityListElement : public SelectableValueButton
{
public:
    explicit UtilityListElement(QString name = "", int recoilIntensity = 0, int recoilCount = 0, int vibrationIntensity = 0, int vibrationCount = 0, QWidget* parent = 0);

    QString getName();
    int getRecoilIntensity();
    int getRecoilCount();
    int getVibrationIntensity();
    int getVibrationCount();
    void setName(QString name);
    void setRecoilIntensity(int intensity);
    void setRecoilCount(int count);
    void setVibrationIntensity(int intensity);
    void setVibrationCount(int count);

signals:

public slots:

private:
    static int idCounter;

    QString name;
    int recoilIntensity;
    int recoilCount;
    int vibrationIntensity;
    int vibrationCount;


};

#endif // UTILITYLISTELEMENT_H
