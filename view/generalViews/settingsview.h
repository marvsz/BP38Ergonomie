#ifndef SETTINGSVIEW_H
#define SETTINGSVIEW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include "navigation/simplenavigateablewidget.h"

class SettingsView : public SimpleNavigateableWidget
{
    Q_OBJECT
public:
    explicit SettingsView(QWidget *parent = 0);
    bool canGoForward() const {
        return false;
    }
signals:
    void resetRecordings();
    void resetDatabase();

private slots:
    void btnResetClicked();

private:
    QPushButton *btnResetRecordings;
    QPushButton *btnReset;
};

#endif // SETTINGSVIEW_H
