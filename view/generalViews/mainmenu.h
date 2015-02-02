#ifndef MAINMENU_H
#define MAINMENU_H

#include "navigation/simplenavigateablewidget.h"
#include <QPushButton>
#include <QWidget>
#include <QLabel>
class MainMenu : public SimpleNavigateableWidget
{
    Q_OBJECT
public:
    explicit MainMenu(QWidget *btnparent = 0);

    bool canGoBack() const{
        return false;
    }

    bool hasAdditionalNavigation() const{
        return true;
    }

    QList<QAbstractButton*> * getAdditionalNavigation() const;

private slots:
    void btnSettingsClicked();
    void btnMetaDataViewClicked();
    void btnWorkplaceListClicked();
    void btnRessourceManagementClicked();
    void btnShiftClicked();

private:
    QLabel *lblViewName;
    QPushButton *btnMetaDataView;
    QPushButton *btnWorkplaceList;
    QPushButton *btnRessourceManagement;
    QPushButton *btnShift;
    QPushButton *btnSettings;

};

#endif // MAINMENU_H
