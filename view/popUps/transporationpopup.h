#ifndef TRANSPORATIONPOPUP_H
#define TRANSPORATIONPOPUP_H

#include "../navigation/abstractpopupwidget.h"
#include "../numberlineedit.h"
#include "../optionselectioncontrol.h"

class TransporationPopUp : public AbstractPopUpWidget
{
    Q_OBJECT
public:
    explicit TransporationPopUp(QWidget *parent = 0);
    ~TransporationPopUp();

    QString getName() const;
    int getWeight() const;
    int getMaxLoad() const;
    bool getHasFixedRoller() const;
    bool getHasBrakes() const;

public slots:
    void onEnter();

private:
    TextLineEdit *txtBxName;
    NumberLineEdit *numBxWeight;
    NumberLineEdit *numBxMaxLoad;
    OptionSelectionControl *oscFixedRoller;
    OptionSelectionControl *oscBrakes;

    const QStringList YES_NO_TEXTS = QStringList()<<tr("yes")<<tr("no");
    const QVector<QVariant> YES_NO_VALUE = QVector<QVariant>()<<true<<false;
};

#endif // TRANSPORATIONPOPUP_H
