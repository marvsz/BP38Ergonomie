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

signals:
    void back();
    void saveProduct();
    void deleteProduct(int id);

public slots:
    void setProduct(const QString &name, const QString &number, int totalPercentage);
    void addProduct(int id, const QString &name, const QString &productNumber, int totalPercentage);
    void clear();

private slots:
    void btnAddClicked();

private:
    static const QList<QStringList> productItemScheme;

    QScrollArea *scProducts;
    QLabel *lblAddProduct;
    QLabel *lblViewName;
    QLabel *lblName;
    QLabel *lblNumber;
    QLabel *lblTotalPercentage;

    TextLineEdit *txtBxName;
    TextLineEdit *txtBxNumber;
    NumberLineEdit *numBxTotalPercentage;

    QPushButton *btnBack;
    QPushButton *btnAdd;

    QVBoxLayout *productListLayout;
};

#endif // PRODUCTVIEW_H
