#include "themepopup.h"
#include <QVBoxLayout>
#include "../view/iconconstants.h"

ThemePopUp::ThemePopUp(QWidget *parent) :
    AbstractPopUpWidget(ConfirmMode::ACCEPT, tr("Change Theme"), parent),
    blue(new DetailedListItem(0, IconConstants::ICON_BLUE, tr("Blue"), QList<QStringList>(), false, true, false, false, false)),
    green(new DetailedListItem(0, IconConstants::ICON_GREEN, tr("Green"), QList<QStringList>(), false, true, false, false, false)),
    themes(new QList<DetailedListItem*>())
{
    QVBoxLayout *layout = new QVBoxLayout;

    themes->append(blue);
    themes->append(green);

    for(int i = 0; i < themes->length(); ++i){
        DetailedListItem *theme = themes->at(i);
        theme->setID(i);
        connect(theme, SIGNAL(selected(int)), this, SLOT(selectedThemeChanged(int)));
        connect(this, SIGNAL(themeSelected(int)), theme, SLOT(selectExclusiveWithID(int)));
        layout->addWidget(theme);
    }

    setLayout(layout);
}

ThemePopUp::~ThemePopUp()
{

}

void ThemePopUp::selectedThemeChanged(int id){
    selectedThemeID = id;
    emit themeSelected(id);
}

int ThemePopUp::getSelectedTheme() const{
    return selectedThemeID;
}

void ThemePopUp::setSelectedTheme(int id){
    selectedThemeChanged(id);
}
