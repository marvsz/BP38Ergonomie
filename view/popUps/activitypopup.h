#ifndef ACTIVITYPOPUP_H
#define ACTIVITYPOPUP_H

#include "../view/navigation/abstractpopupwidget.h"
#include <QScrollArea>
#include <QVBoxLayout>
#include "../view/textlineedit.h"
#include "../view/numberlineedit.h"

class ActivityPopUp : public AbstractPopUpWidget
{
    Q_OBJECT
public:
    explicit ActivityPopUp(QWidget *parent = 0);
    ~ActivityPopUp();

    QString getDescription() const;
    int getRepetitions() const;
    int getSelectedProduct() const;

signals:
    void selectedProduct(int id);

public slots:
    void setActivity(const QString &description, int repetitions, int selectedProductID);
    void addProduct(int id, const QString &name, const QString &productNumber);
    void clearProducts();
    void setSelectedProduct(int id);

private slots:
    void selectedProductChanged(int id);

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
