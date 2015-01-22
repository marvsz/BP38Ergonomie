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

public slots:

private:
    QLabel *lblViewName;
    QPushButton *btnBack;

};

#endif // SETTINGSVIEW_H
