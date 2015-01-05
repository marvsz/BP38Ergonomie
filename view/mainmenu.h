#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>
#include <QPushButton>
#include <QWidget>

class MainMenu : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainMenu(QWidget *parent = 0);

signals:
    void metaDataViewSelected();
    void workplaceListViewSelected();
    void newRecordingViewSelected();

public slots:
    void openMetaDataView();
    void openWorkplaceListView();
    void openNewRecordingView();

private:
    QPushButton *metaDataViewBtn;
    QPushButton *workplaceListBtn;
    QPushButton *newRecordingBtn;
};

#endif // MAINMENU_H
