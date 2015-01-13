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

class ActivityView : public QWidget
{
    Q_OBJECT
public:
    explicit ActivityView(QWidget *parent = 0);

    QString getDescription() const;
    int getRepetitions() const;
    int getSelectedProduct() const;

signals:
    void back();
    void showProductView();
    void productSelected(int id);
    void deleteActivity(int id);
    void showWorkProcessView(int id);
    void saveActivity();

public slots:
    void addProduct(int id, const QString &name, const QString &productNumber);
    void clearProducts();
    void setSelectedProduct(int id);

    void setActivity(const QString &description, int repetitions, int selectedProductID);
    void addActivity(int id, const QString &description, int repetitions);
    void clearActivities();

private slots:
    void btnBackClicked();
    void btnAddClicked();
    void selectedProductChanged(int id);

private:
    static const QList<QStringList> productItemScheme;
    static const QList<QStringList> activityItemScheme;

    int id;
    int selectedProductID;

    QVBoxLayout *mainLayout;
    QVBoxLayout *productListLayout;
    QVBoxLayout *activityListLayout;

    QLabel *lblViewName;
    QPushButton *btnBack;

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
