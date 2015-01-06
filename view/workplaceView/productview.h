#ifndef PRODUCTVIEW_H
#define PRODUCTVIEW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
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
    void saveSelectedProduct(int id);

public slots:
    void setProduct(const QString &name, const QString &number, int totalPercentage);
    void addProduct(int id, const QString &name);
    void clearProducts();

private slots:
    void btnBackClicked();
    void btnAddClicked();

private:
    QLabel *lblViewName;
    QLabel *lblName;
    QLabel *lblNumber;
    QLabel *lblTotalPercentage;

    TextLineEdit *txtBxName;
    TextLineEdit *txtBxNumber;
    NumberLineEdit *numBxTotalPercentage;

    QPushButton *btnBack;
    QPushButton *btnAdd;

    QVBoxLayout *produktListLayout;
};

#endif // PRODUCTVIEW_H
