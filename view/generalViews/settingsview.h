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
    void setCurrentLanguageIcon(const QString &objectName);
    void setCurrentThemeIcon(const QString &objectName);

private slots:
    void btnImportDataClicked();
    void btnResetClicked();
    void btnSelectLanguageClicked();
    void btnSelectThemeClicked();

private:
    IconButton *btnImportData;
    IconButton *btnResetRecordings;
    IconButton *btnReset;
    IconButton *btnSelectLanguage;
    IconButton *btnSelectTheme;
};

#endif // SETTINGSVIEW_H
