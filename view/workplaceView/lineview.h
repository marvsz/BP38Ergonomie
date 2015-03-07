#ifndef LINEVIEW_H
#define LINEVIEW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QList>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QScrollArea>
#include "../detailedlistitem.h"
#include "../numberlineedit.h"
#include "../textedit.h"
#include "../interfaces/ilinelist.h"
#include "../navigation/simplenavigateablewidget.h"

class LineView : public SimpleNavigateableWidget, ILineList
{
    Q_OBJECT
    Q_INTERFACES(ILineList)
public:
    explicit LineView(QWidget *parent = 0);
    ~LineView();

signals:
    void createLine(QHash<QString, QVariant> values);
    void deleteLine(int id);
    void selectLine(int id);
    void editLine(int id);

    void lineSelected(int id);

public slots:
    void addLine(QHash<QString, QVariant> values);
    void updateLine(QHash<QString, QVariant> values);
    void removeLine(int id);
    void selectedLine(QHash<QString, QVariant> values);
    void clearLines();
    void onLeaving();

private slots:
    void btnAddClicked();
    void selectedLineChanged(int id);
    void editLineClicked(int id);

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
