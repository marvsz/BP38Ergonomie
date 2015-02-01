#ifndef LINEVIEW_H
#define LINEVIEW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QList>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QScrollArea>
#include "detailedlistitem.h"
#include "numberlineedit.h"
#include "textedit.h"
#include "../navigation/simplenavigateablewidget.h"

class LineView : public SimpleNavigateableWidget
{
    Q_OBJECT
public:
    explicit LineView(QWidget *parent = 0);
    ~LineView();

    bool canGoForward() const {
        return false;
    }

    QString getName() const;
    QString getDescription() const;
    int getWorkplaceCount() const;

signals:
    void saveLine();
    void saveSelectedLine(int id);
    void deleteLine(int id);
    void lineSelected(int id);

public slots:
    void setLine(const QString &name, const QString &description, int workplaceCount);
    void addLine(int id, const QString &name);
    void clear();
    void setSelectedLine(int id);

private slots:
    void btnAddClicked();
    void selectedLineChanged(int id);

private:
    int selectedLineID;
    QVBoxLayout *listContentLayout;
    QScrollArea *scLines;

    QLabel *lblSelectLine;
    QLabel *lblAddLine;
    QLabel *lblName;
    QLabel *lblWorkplaceCount;
    QLabel *lblDescription;

    TextLineEdit *txtBxName;
    NumberLineEdit *numBxWorkplaceCount;
    TextEdit *txtBxDescription;

    QPushButton *btnAdd;
};

#endif // LINEVIEW_H
