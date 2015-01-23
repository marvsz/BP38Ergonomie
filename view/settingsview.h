#ifndef SETTINGSVIEW_H
#define SETTINGSVIEW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

class SettingsView : public QWidget
{
    Q_OBJECT
public:
    explicit SettingsView(QWidget *parent = 0);

signals:
    void back();
    void resetDatabase();
    void showAnalystSelectionView();

public slots:

private slots:
    void btnResetClicked();
private:
    QLabel *lblViewName;
    QPushButton *btnBack;

    QPushButton *btnReset;
};

#endif // SETTINGSVIEW_H
