#ifndef LINEVIEW_H
#define LINEVIEW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QList>
#include <QCheckBox>
#include <QVBoxLayout>
#include "detailedlistitem.h"
#include "numberlineedit.h"
#include "textedit.h"

class LineView : public QWidget
{
    Q_OBJECT
public:
    explicit LineView(QWidget *parent = 0);
    ~LineView();

    QString getName() const;
    QString getDescription() const;
    int getWorkplaceCount() const;

signals:
    void back();
    void saveLine();
    void saveSelectedLine(int id);
    void deleteLine(int id);
    void lineSelected(int id);

public slots:
    void setLine(const QString &name, const QString &description, int workplaceCount);
    void addLine(int id, const QString &name);
    void clearLines();
    void setSelectedLine(int id);

private slots:
    void btnBackClicked();
    void btnAddCicked();
    void btnDeleteClicked(int id);
    void selectedLineChanged(int id);

private:
    int selectedLineID;
    DetailedListItem* selectedItem;
    QVBoxLayout *listContentLayout;
    QLabel *lblViewName;
    QLabel *lblSelectLine;
    QLabel *lblAddLine;
    QLabel *lblName;
    QLabel *lblWorkplaceCount;
    QLabel *lblDescription;

    TextLineEdit *txtBxName;
    NumberLineEdit *numBxWorkplaceCount;
    TextEdit *txtBxDescription;

    QPushButton *btnBack;
    QPushButton *btnAdd;
};

#endif // LINEVIEW_H
