#ifndef LINEPOPUP_H
#define LINEPOPUP_H
#include "../navigation/abstractpopupwidget.h"
#include "../textlineedit.h"
#include "../numberlineedit.h"
#include "../textedit.h"

class LinePopUp : public AbstractPopUpWidget
{
    Q_OBJECT
public:
    explicit LinePopUp(QWidget *parent = 0);

signals:

public slots:

private:
    TextLineEdit *txtBxName;
    NumberLineEdit *numBxWorkplaceCount;
    TextEdit *txtBxDescription;

};

#endif // LINEPOPUP_H
