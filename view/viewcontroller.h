#ifndef VIEWCONTROLLER_H
#define VIEWCONTROLLER_H

#include <QStackedWidget>
#include "mainmenu.h"
#include "metadataview.h"
#include "documentationview.h"

class ViewController : public QStackedWidget
{
    Q_OBJECT
public:
    explicit ViewController(QWidget *parent = 0);
    static const int MAIN_MENU_VIEW = 0;
    static const int METADATA_VIEW = 1;
    static const int DOCUMENTATION_VIEW = 2;

signals:

public slots:
    void setMainMenuView();
    void setMetaDataView();
    void setDocumentationView();

private:
    MainMenu *mainMenuView;
    MetaDataView *metaDataView;
    DocumentationView *documentationView;
};

#endif // VIEWCONTROLLER_H
