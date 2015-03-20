#ifndef ANALYSTPOPUP_H
#define ANALYSTPOPUP_H

#include "../navigation/abstractpopupwidget.h"
#include "../interfaces/ianalyst.h"
#include "../../databaseHandler/dbconstants.h"
#include "../textlineedit.h"

class AnalystPopUp : public AbstractPopUpWidget, IAnalyst
{
    Q_OBJECT
    Q_INTERFACES(IAnalyst)
public:
    explicit AnalystPopUp(QWidget *parent = 0);
    ~AnalystPopUp();

signals:
    void saveAnalyst(QHash<QString, QVariant> values);

public slots:
    void onEnter();
    void setAnalyst(QHash<QString, QVariant>){}

private slots:
    void onConfirm();

private:
    TextLineEdit *txtBxAnalystLastName;
    TextLineEdit *txtBxAnalystFirstName;
    TextLineEdit *txtBxAnalystEmployer;
    TextLineEdit *txtBxAnalystExperience;

};

#endif // ANALYSTPOPUP_H
