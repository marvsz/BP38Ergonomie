#ifndef TRANSPORATIONPOPUP_H
#define TRANSPORATIONPOPUP_H

#include "../navigation/abstractpopupwidget.h"
#include "../numberlineedit.h"
#include "../optionselectioncontrol.h"
#include "../interfaces/itransportation.h"

class TransporationPopUp : public AbstractPopUpWidget, ITransportation
{
    Q_OBJECT
    Q_INTERFACES(ITransportation)
public:
    explicit TransporationPopUp(QWidget *parent = 0);
    ~TransporationPopUp();

signals:
    void saveTransportation(QHash<QString, QVariant> values);

public slots:
    void setTransportation(QHash<QString, QVariant>){}

    void onConfirm();
    void onClose();

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
