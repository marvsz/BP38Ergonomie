#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QPushButton>
#include <QWidget>
#include <QLabel>
class MainMenu : public QWidget
{
    Q_OBJECT
public:
    explicit MainMenu(QWidget *btnparent = 0);

signals:
    void showMetaDataView();
    void showWorkplaceListView();
    void showRessourceManagementView();
    void showNewRecordingView();
    void showSettingsView();


private:
    QLabel *lblViewName;
    QPushButton *btnMetaDataView;
    QPushButton *btnWorkplaceList;
    QPushButton *btnRessourceManagement;
    QPushButton *btnSettings;

};

#endif // MAINMENU_H
