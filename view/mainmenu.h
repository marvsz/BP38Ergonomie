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
    void newWorkplaceViewSelected();
    void newRecordingViewSelected();

public slots:
    void openMetaDataView();
    void openNewWorkplaceView();
    void openNewRecordingView();

private:
    QPushButton *metaDataViewBtn;
    QPushButton *newWorkplaceBtn;
    QPushButton *newRecordingBtn;
};

#endif // MAINMENU_H
