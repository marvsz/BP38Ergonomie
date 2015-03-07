#ifndef ACTIVITYVIEW_H
#define ACTIVITYVIEW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QScrollArea>
#include "../textlineedit.h"
#include "../numberlineedit.h"
#include "../navigation/simplenavigateablewidget.h"
#include "../interfaces/iproductlist.h"

class ActivityView : public SimpleNavigateableWidget, IProductList
{
    Q_OBJECT
    Q_INTERFACES(IProductList)
public:
    explicit ActivityView(QWidget *parent = 0);

    QString getDescription() const;
    int getRepetitions() const;
    int getSelectedProduct() const;

signals:
    void deleteActivity(int id);
    void selectedProduct(int id);
    void createActivity();
    void selectActivity(int id);
    void editActivity(int id);

    void createProduct(QHash<QString, QVariant> values);
    void deleteProduct(int id);

public slots:
    void setSelectedProduct(int id);

    void setActivity(const QString &description, int repetitions, int selectedProductID);
    void addActivity(int id, const QString &description, int repetitions);
    void clearActivities();

    void addProduct(QHash<QString, QVariant> values);
    void updateProduct(QHash<QString, QVariant> values);
    void removeProduct(int id);
    void clearProducts();

private slots:
    void btnAddClicked();
    void btnProductsClicked();
    void workprocessClicked();
    void selectedProductChanged(int id);

    void editActivityClicked(int id);

private:
    const QList<QStringList> productItemScheme = QList<QStringList>() << (QStringList() << tr("product number"));
    const QList<QStringList> activityItemScheme = QList<QStringList>() << (QStringList() << tr("repetitions"));

    int id;
    int selectedProductID;

    QVBoxLayout *mainLayout;
    QVBoxLayout *productListLayout;
    QVBoxLayout *activityListLayout;

    QWidget *productListContent;
    QWidget *activityListContent;
    QScrollArea *scProducts;
    QScrollArea *scActivities;

    QLabel *lblAddActivity;
    QLabel *lblActivityDescription;
    QLabel *lblActivityRepetitions;
    QLabel *lblChooseProduct;
    TextLineEdit *txtBxActivityDescription;
    NumberLineEdit *numBxActivityRepetitions;
    QPushButton *btnAdd;
    QPushButton *btnMoreProducts;
};

#endif // ACTIVITYVIEW_H
