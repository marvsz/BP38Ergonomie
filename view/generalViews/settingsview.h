#ifndef SETTINGSVIEW_H
#define SETTINGSVIEW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include "navigation/simplenavigateablewidget.h"
#include "../view/iconbutton.h"

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

public slots:
    void setCurrentLanguageIcon(const QString &iconPath);
    void setCurrentThemeIcon(const QString &iconPath);

private slots:
    void btnResetClicked();
    void btnSelectLanguageClicked();
    void btnSelectThemeClicked();

private:
    IconButton *btnResetRecordings;
    IconButton *btnReset;
    IconButton *btnSelectLanguage;
    IconButton *btnSelectTheme;
};

#endif // SETTINGSVIEW_H
