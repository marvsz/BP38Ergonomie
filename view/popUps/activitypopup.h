#ifndef ACTIVITYPOPUP_H
#define ACTIVITYPOPUP_H

#include "../navigation/abstractpopupwidget.h"
#include <QScrollArea>
#include <QVBoxLayout>
#include "../textlineedit.h"
#include "../numberlineedit.h"
#include "../interfaces/iproductlist.h"
#include "../../databaseHandler/dbconstants.h"

class ActivityPopUp : public AbstractPopUpWidget, IProductList
{
    Q_OBJECT
    Q_INTERFACES(IProductList)
public:
    explicit ActivityPopUp(QWidget *parent = 0);
    ~ActivityPopUp();

    QString getDescription() const;
    int getRepetitions() const;
    int getSelectedProduct() const;

signals:
    void selectedProduct(int id);

    void createProduct(QHash<QString, QVariant> values);
    void deleteProduct(int id);

public slots:
    void setActivity(const QString &description, int repetitions, int selectedProductID);
    void setSelectedProduct(int id);

    void addProduct(QHash<QString, QVariant> values);
    void updateProduct(QHash<QString, QVariant> values);
    void removeProduct(int id);
    void clearProducts();

private slots:
    void selectedProductChanged(int id);

    void onConfirm();
    void onCancel();
    void onClose();

private:
    const QList<QStringList> productItemScheme = QList<QStringList>() << (QStringList() << tr("product number"));

    int selectedProductID;

    QVBoxLayout *productListLayout;
    QWidget *productListContent;
    QScrollArea *scProducts;

    QLabel *lblActivityDescription;
    QLabel *lblActivityRepetitions;
    QLabel *lblChooseProduct;
    TextLineEdit *txtBxActivityDescription;
    NumberLineEdit *numBxActivityRepetitions;

};

#endif // ACTIVITYPOPUP_H
