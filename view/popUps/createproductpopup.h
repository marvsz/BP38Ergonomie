#ifndef CREATEPRODUCTPOPUP_H
#define CREATEPRODUCTPOPUP_H

#include "../navigation/abstractpopupwidget.h"
#include "../textlineedit.h"
#include "../numberlineedit.h"
#include "../interfaces/iproduct.h"
#include "../../databaseHandler/dbconstants.h"

class CreateProductPopUp : public AbstractPopUpWidget, IProduct
{
    Q_OBJECT
    Q_INTERFACES(IProduct)
public:
    explicit CreateProductPopUp(QWidget *parent = 0);
    ~CreateProductPopUp();

signals:
    void saveProduct(QHash<QString, QVariant> values);

public slots:
    void setProduct(QHash<QString, QVariant>){}

private slots:
    void onConfirm();
    void onClose();

private:
    TextLineEdit *txtBxName;
    TextLineEdit *txtBxNumber;
    NumberLineEdit *numBxTotalPercentage;

};

#endif // CREATEPRODUCTPOPUP_H
