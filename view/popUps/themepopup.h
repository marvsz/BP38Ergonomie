#ifndef THEMEPOPUP_H
#define THEMEPOPUP_H

#include <QList>
#include "../navigation/abstractpopupwidget.h"
#include "../detailedlistitem.h"

class ThemePopUp : public AbstractPopUpWidget
{
    Q_OBJECT
public:
    explicit ThemePopUp(QWidget *parent = 0);
    ~ThemePopUp();

    int getSelectedTheme() const;

signals:
    void themeSelected(int id);

public slots:
    void setSelectedTheme(int id);

private slots:
    void selectedThemeChanged(int id);

private:
    int selectedThemeID;
    DetailedListItem *blue;
    DetailedListItem *green;
    QList<DetailedListItem*> *themes;
};

#endif // THEMEPOPUP_H
