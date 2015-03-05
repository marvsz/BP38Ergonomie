#ifndef ANALYSTPOPUP_H
#define ANALYSTPOPUP_H

#include "../navigation/abstractpopupwidget.h"
#include "../textlineedit.h"

class AnalystPopUp : public AbstractPopUpWidget
{
    Q_OBJECT
public:
    explicit AnalystPopUp(QWidget *parent = 0);
    ~AnalystPopUp();

    QString getAnalystLastName() const;
    QString getAnalystFirstName() const;
    QString getAnalystEmployer() const;
    QString getAnalystExperience() const;

public slots:
    void onEnter();

private:
    TextLineEdit *txtBxAnalystLastName;
    TextLineEdit *txtBxAnalystFirstName;
    TextLineEdit *txtBxAnalystEmployer;
    TextLineEdit *txtBxAnalystExperience;

};

#endif // ANALYSTPOPUP_H
