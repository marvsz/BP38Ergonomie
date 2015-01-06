#ifndef WORKPLACEVIEW_H
#define WORKPLACEVIEW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "numberlineedit.h"

class WorkplaceView : public QWidget
{
    Q_OBJECT
public:
    explicit WorkplaceView(QWidget *parent = 0);
    explicit WorkplaceView(int id, QWidget *parent = 0);

signals:
    void save(int id);
    void save();
    void goOnToWorkProcesses();
    void cancle();

public slots:
    void setWorkplaceMetaData(const QString &name, const QString &description, const QString &code, int percentageWoman);

private slots:
    void btnSaveClicked();
    void btnCancelClicked();
    void btnGoOnWithWorkProcessesClicked();

private:
    int id;

    QLabel *lblViewDescription;
    QLabel *lblName;
    QLabel *lblDescription;
    QLabel *lblCode;
    QLabel *lblPercentageWoman;

    TextLineEdit *txtBxName;
    TextLineEdit *txtBxDescription;
    TextLineEdit *txtBxCode;
    NumberLineEdit *numBxWomanPercentage;

    QPushButton *btnCancel;
    QPushButton *btnSave;
    QPushButton *btnGoOnWithWorkProcesses;
};

#endif // WORKPLACEVIEW_H
