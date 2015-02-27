#ifndef LANGUAGEPOPUP_H
#define LANGUAGEPOPUP_H

#include "navigation/abstractpopupwidget.h"
#include "detailedlistitem.h"

class LanguagePopUp : public AbstractPopUpWidget
{
public:
    explicit LanguagePopUp(QWidget *parent = 0);
    ~LanguagePopUp();

private:
    DetailedListItem *german;
    DetailedListItem *english;
};

#endif // LANGUAGEPOPUP_H
