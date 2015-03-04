#ifndef SETTINGSVIEW_H
#define SETTINGSVIEW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include "../navigation/simplenavigateablewidget.h"
#include "../iconbutton.h"

class SettingsView : public SimpleNavigateableWidget
{
    Q_OBJECT
public:
    explicit SettingsView(QWidget *parent = 0);
    bool canGoForward() const {
        return false;
    }
signals:
    void resetDatabase();

public slots:
    void setCurrentLanguageIcon(const QString &objectName);
    void setCurrentThemeIcon(const QString &objectName);

private slots:
    void btnResetRecordingsClicked();
    void btnRestoreFactoryClicked();
    void btnSelectLanguageClicked();
    void btnSelectThemeClicked();

private:
    IconButton *btnResetRecordings;
    IconButton *btnRestoreFactory;
    IconButton *btnSelectLanguage;
    IconButton *btnSelectTheme;
};

#endif // SETTINGSVIEW_H
