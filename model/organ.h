#ifndef ORGAN_H
#define ORGAN_H

#include <QString>

class Organ
{
public:
    Organ(QString* organ);
    ~Organ();

    void setOrgan(QString* o);
    QString* getOrgan();

private:
    QString* organ;
};

#endif // ORGAN_H
