#ifndef LINEPOPUP_H
#define LINEPOPUP_H
#include "../navigation/abstractpopupwidget.h"
#include "../textlineedit.h"
#include "../numberlineedit.h"
#include "../textedit.h"
#include "../interfaces/iline.h"

class LinePopUp : public AbstractPopUpWidget, ILine
{
    Q_OBJECT
    Q_INTERFACES(ILine)
public:
    explicit LinePopUp(QWidget *parent = 0);

signals:
    void saveLine(QHash<QString, QVariant> values);

public slots:
    void setLine(QHash<QString, QVariant> values);

private slots:
    void onConfirm();

private:
    int id;
    TextLineEdit *txtBxName;
    NumberLineEdit *numBxWorkplaceCount;
    TextEdit *txtBxDescription;

};

#endif // LINEPOPUP_H
