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
#include "../navigation/simplenavigateablewidget.h"

class ProductView : public SimpleNavigateableWidget
{
    Q_OBJECT
public:
    explicit ProductView(QWidget *parent = 0);
    ~ProductView();

    bool canGoForward() const{
        return false;
    }

    QString getName() const;
    QString getNumber() const;
    int getTotalPercentage() const;

signals:
    void saveProduct();
    void deleteProduct(int id);

public slots:
    void setProduct(const QString &name, const QString &number, int totalPercentage);
    void addProduct(int id, const QString &name, const QString &productNumber, int totalPercentage);
    void clear();

private slots:
    void btnAddClicked();

private:
    const QList<QStringList> productItemScheme = QList<QStringList>() << (QStringList() << tr("product number")) << (QStringList()<< tr("total percentage"));

    QScrollArea *scProducts;
    QLabel *lblAddProduct;
    QLabel *lblName;
    QLabel *lblNumber;
    QLabel *lblTotalPercentage;

    TextLineEdit *txtBxName;
    TextLineEdit *txtBxNumber;
    NumberLineEdit *numBxTotalPercentage;

    QPushButton *btnAdd;

    QVBoxLayout *productListLayout;
};

#endif // PRODUCTVIEW_H
