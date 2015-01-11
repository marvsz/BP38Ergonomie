#ifndef PRODUCTVIEW_H
#define PRODUCTVIEW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHash>
#include <QList>
#include <QScrollArea>
#include "numberlineedit.h"

class ProductView : public QWidget
{
    Q_OBJECT
public:
    explicit ProductView(QWidget *parent = 0);
    ~ProductView();

    QString getName() const;
    QString getNumber() const;
    int getTotalPercentage() const;
    QList<int> getSelectedIDs() const;

signals:
    void back();
    void saveProduct();
    void saveSelectedProducts();
    void deleteProduct(int id);
    void productSelected(int id);

public slots:
    void setProduct(const QString &name, const QString &number, int totalPercentage);
    void addProduct(int id, const QString &name);
    void clearProducts();
    void setProductSelected(int id);

private slots:
    void btnBackClicked();
    void idSelected(int id);
    void idDeselected(int id);

private:
    QHash<int, bool> idSelectionMap;

    QScrollArea *scProducts;
    QLabel *lblViewName;
    QLabel *lblName;
    QLabel *lblNumber;
    QLabel *lblTotalPercentage;

    TextLineEdit *txtBxName;
    TextLineEdit *txtBxNumber;
    NumberLineEdit *numBxTotalPercentage;

    QPushButton *btnBack;
    QPushButton *btnAdd;
    QPushButton *btnDelete;

    QVBoxLayout *productListLayout;
};

#endif // PRODUCTVIEW_H
