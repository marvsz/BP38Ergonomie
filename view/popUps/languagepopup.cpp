#include "languagepopup.h"
#include <QGridLayout>


LanguagePopUp::LanguagePopUp(QWidget *parent):
   AbstractPopUpWidget(ConfirmMode::ACCEPT, tr("Select language"), parent),
   german(new DetailedListItem(this, "germanIcon",  "Deutsch", QList<QStringList>(), false, true, false, false, false)),
   english(new DetailedListItem(this, "englishIcon",  "English", QList<QStringList>(), false, true, false, false, false)),
   languages(new QList<DetailedListItem*>())
{
    languages->append(german);
    languages->append(english);

    QGridLayout *mainLayout = new QGridLayout;

    for(int i = 0; i < languages->length(); ++i){
        DetailedListItem *language = languages->at(i);
        language->setID(i);
        connect(language, SIGNAL(selected(int)), this, SLOT(selectedLanguageChanged(int)));
        connect(this, SIGNAL(languageSelected(int)), language, SLOT(selectExclusiveWithID(int)));
        mainLayout->addWidget(language);
    }

    setLayout(mainLayout);
}

LanguagePopUp::~LanguagePopUp()
{

}

void LanguagePopUp::onEnter(){
    //GET LANGUAGE FROM DATABASE
    //setSelectedLanguage();
}

void LanguagePopUp::selectedLanguageChanged(int id){
    selectedLanguageID = id;
    emit languageSelected(id);
}

int LanguagePopUp::getSelectedLanguage() const{
    return selectedLanguageID;
}

void LanguagePopUp::setSelectedLanguage(int id){
    selectedLanguageChanged(id);
}