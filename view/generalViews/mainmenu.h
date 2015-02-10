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

signals:
    void createBlankRecording();

private slots:
    void btnSettingsClicked();
    void btnMetaDataViewClicked();
    void btnWorkplaceListClicked();
    void btnRessourceManagementClicked();
    void btnShiftClicked();
    void btnNewRecordingClicked();
    void btnSendDatabaseClicked();

private:
    QLabel *lblViewName;
    QPushButton *btnMetaDataView;
    QPushButton *btnWorkplaceList;
    QPushButton *btnRessourceManagement;
    QPushButton *btnShift;
    QPushButton *btnSettings;
    QPushButton *btnNewRecording;
    QPushButton *btnSendDatabase;

};

#endif // MAINMENU_H
