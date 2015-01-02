#ifndef APPLIEDFORCE_H
#define APPLIEDFORCE_H

#include <QString>

class AppliedForce
{
public:
    AppliedForce(QString *organ, QString *direction);
    AppliedForce();

    int getID() const;

    QString* getOrgan() const;
    void setOrgan(QString *organ);

    QString* getDirection() const;
    void setDirection(QString *direction);

    int getIntensity() const;
    void setIntensity(int intensity);

private:
    int id;
    QString *organ;
    QString *direction;
    int intensity;
};

#endif // APPLIEDFORCE_H
