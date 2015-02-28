#ifndef LANGUAGEPOPUP_H
#define LANGUAGEPOPUP_H

#include "navigation/abstractpopupwidget.h"
#include "detailedlistitem.h"
#include <QList>

class LanguagePopUp : public AbstractPopUpWidget
{
    Q_OBJECT
public:
    explicit LanguagePopUp(QWidget *parent = 0);
    ~LanguagePopUp();

signals:
    void languageSelected(int id);

private:
    DetailedListItem *german;
    DetailedListItem *english;
    QList<DetailedListItem*> *languages;

};

#endif // LANGUAGEPOPUP_H
