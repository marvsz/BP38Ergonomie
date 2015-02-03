#ifndef ACTIVITYVIEW_H
#define ACTIVITYVIEW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QScrollArea>
#include "textlineedit.h"
#include "numberlineedit.h"
#include "../navigation/simplenavigateablewidget.h"

class ActivityView : public SimpleNavigateableWidget
{
    Q_OBJECT
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

public slots:
    void addProduct(int id, const QString &name, const QString &productNumber);
    void clearProducts();
    void setSelectedProduct(int id);

    void setActivity(const QString &description, int repetitions, int selectedProductID);
    void addActivity(int id, const QString &description, int repetitions);
    void clearActivities();

private slots:
    void btnAddClicked();
    void btnProductsClicked();
    void workprocessClicked();
    void selectedProductChanged(int id);

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
