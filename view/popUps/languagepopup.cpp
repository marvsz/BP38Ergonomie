#include "languagepopup.h"
#include <QGridLayout>
#include "iconconstants.h"

LanguagePopUp::LanguagePopUp(QWidget *parent):
   AbstractPopUpWidget(ConfirmMode::ACCEPT, tr("Select language"), parent),
   german(new DetailedListItem(this, IconConstants::ICON_LINE,  "Deutsch", QList<QStringList>(), false, true, false, false, false)),
   english(new DetailedListItem(this, IconConstants::ICON_LINE,  "English", QList<QStringList>(), false, true, false, false, false))
{
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(german);
    mainLayout->addWidget(english);

    setLayout(mainLayout);
}

LanguagePopUp::~LanguagePopUp()
{

}


