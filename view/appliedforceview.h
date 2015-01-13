#ifndef ACTIONFORCEVIEW_H
#define ACTIONFORCEVIEW_H

#include <QMainWindow>
#include <QScrollArea>
#include <QVector>
#include <QString>
#include "valuecontrol.h"

class AppliedForceView : public QWidget
{
    Q_OBJECT
public:
    explicit AppliedForceView(QWidget *parent = 0);

    int getIntensity() const;
    QString getOrgan() const;
    QString getDirection() const;

signals:

public slots:
    //void setValues(const QString &organ, const QString &direction, int intensity);
    void setOrgan(const QString &organ);
    void setDirection(const QString &direction);
    void setIntensity(int &intensity);

private:
    static const QVector<QString> ORGAN_TEXTS;
    static const QVector<QString> DIRECTION_TEXTS;
    static const QVector<QString> DIRECTION_VALUES;
    static const QVector<int> INTENSITY_VALUES;

    ValueControl* valConIntensity;
    ValueControl* valConDirection;
    ValueControl* valConOrgan;

};

#endif // ACTIONFORCEVIEW_H
