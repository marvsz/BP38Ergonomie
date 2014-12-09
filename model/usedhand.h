#ifndef USEDHAND_H
#define USEDHAND_H

#include <QString>

class UsedHand
{
public:
    UsedHand(QString* hand);
    ~UsedHand();

    void setHand(QString* h);
    QString* getHand();


private:
    QString* hand;
};

#endif // USEDHAND_H
