#ifndef MAINMENU_H
#define MAINMENU_H

#include "navigation/simplenavigateablewidget.h"
#include "../view/iconbutton.h"
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

signals:
    void createBlankRecording();

protected:
    void changeEvent(QEvent* e);

private slots:
    void retranslate();

    void btnSettingsClicked();
    void btnMetaDataViewClicked();
    void btnWorkplaceListClicked();
    void btnRessourceManagementClicked();
    void btnShiftClicked();
    void btnNewRecordingClicked();
    void btnSendDatabaseClicked();

private:
    QLabel *lblViewName;
    IconButton *btnMetaDataView;
    IconButton *btnWorkplaceList;
    IconButton *btnRessourceManagement;
    IconButton *btnShift;
    QPushButton *btnSettings;
    QPushButton *btnNewRecording;
    QPushButton *btnSendDatabase;

};

#endif // MAINMENU_H
