#ifndef PRODUCTPOPUP_H
#define PRODUCTPOPUP_H

#include "../view/navigation/abstractpopupwidget.h"
#include "../view/textlineedit.h"
#include "../view/numberlineedit.h"

class ProductPopUp : public AbstractPopUpWidget
{
    Q_OBJECT
public:
    explicit ProductPopUp(QWidget *parent = 0);
    ~ProductPopUp();

    QString getName() const;
    QString getNumber() const;
    int getTotalPercentage() const;

public slots:
    void onEnter();

private:
    TextLineEdit *txtBxName;
    TextLineEdit *txtBxNumber;
    NumberLineEdit *numBxTotalPercentage;

};

#endif // PRODUCTPOPUP_H
