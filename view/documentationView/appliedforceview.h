#ifndef ACTIONFORCEVIEW_H
#define ACTIONFORCEVIEW_H

#include "view/navigation/titledwidget.h"
#include <QScrollArea>
#include <QVector>
#include <QString>
#include "../valuecontrol.h"

class AppliedForceView : public TitledWidget
{
    Q_OBJECT
public:
    explicit AppliedForceView(QWidget *parent = 0);

    int getIntensity() const;
    QString getOrgan() const;
    QString getDirection() const;

signals:

public slots:
    void setOrgan(const QString &organ);
    void setDirection(const QString &direction);
    void setIntensity(int intensity);

private:
    const QVector<QString> ORGAN_TEXTS = QVector<QString>()<<tr("finger")<<tr("hand")<<tr("arm")<<tr("foot/leg")<<tr("full body");
    const QVector<QString> DIRECTION_TEXTS = QVector<QString>()<<tr("above")<<tr("below")<<tr("front")<<tr("back")<<tr("right")<<tr("left");
    const QVector<QString> DIRECTION_VALUES = QVector<QString>()<<tr("+A")<<tr("-A")<<tr("+B")<<tr("-B")<<tr("+C")<<tr("-C");
    static const QVector<int> INTENSITY_VALUES;

    ValueControl* valConIntensity;
    ValueControl* valConDirection;
    ValueControl* valConOrgan;

};

#endif // ACTIONFORCEVIEW_H
