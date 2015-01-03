#include "viewcontroller.h"

ViewController::ViewController(QWidget *parent) :
    QStackedWidget(parent)
{
    mainMenuView = new MainMenu;
    metaDataView = new MetaDataView;
    documentationView = new DocumentationView;

    connect(mainMenuView, SIGNAL(metaDataViewSelected()), this, SLOT(setMetaDataView()));
    connect(mainMenuView, SIGNAL(newRecordingViewSelected()), this, SLOT(setDocumentationView()));

    connect(metaDataView, SIGNAL(showMainMenu()), this, SLOT(setMainMenuView()));
    connect(documentationView, SIGNAL(showMainMenu()), this, SLOT(setMainMenuView()));

    this->addWidget(mainMenuView);
    this->addWidget(metaDataView);
    this->addWidget(documentationView);

    setCurrentIndex(ViewController::MAIN_MENU_VIEW);
}

void ViewController::setMainMenuView(){
    setCurrentIndex(ViewController::MAIN_MENU_VIEW);
}

void ViewController::setMetaDataView(){
    setCurrentIndex(ViewController::METADATA_VIEW);
}

void ViewController::setDocumentationView(){
    setCurrentIndex(ViewController::DOCUMENTATION_VIEW);
}
