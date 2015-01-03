#ifndef METADATAVIEW_H
#define METADATAVIEW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QDateTimeEdit>
#include "numberlineedit.h"

class MetaDataView : public QWidget
{
    Q_OBJECT
public:
    explicit MetaDataView(QWidget *parent = 0);

signals:
    void showMainMenu();

public slots:

private slots:

    void backButtonClicked();

private:

    QPushButton *btnBack;
    QLabel *lblViewDescription;
    QPushButton *btnForward;

    QLabel *lblAnalyst;
    QLabel *lblAnalystLastName;
    QLabel *lblAnalystFirstName;
    QLabel *lblAnalystEmployer;
    QLabel *lblAnalystExperience;

    TextLineEdit *txtBxAnalystLastName;
    TextLineEdit *txtBxAnalystFirstName;
    TextLineEdit *txtBxAnalystEmployer;
    TextLineEdit *txtBxAnalystExperience;

    QLabel *lblCorporation;
    QLabel *lblCorpName;
    TextLineEdit *txtBxCorpName;

    QLabel *lblFactory;
    QLabel *lblFactoryName;
    QLabel *lblFactoryStreet;
    QLabel *lblFactoryCity;
    QLabel *lblFactoryZip;
    QLabel *lblFactoryCountry;
    QLabel *lblFactoryContact;
    QLabel *lblFactoryEmployeeCount;

    TextLineEdit *txtBxFactoryName;
    TextLineEdit *txtBxFactoryStreet;
    TextLineEdit *txtBxFactoryCity;
    NumberLineEdit *txtBxFactoryZip;
    TextLineEdit *txtBxFactoryCountry;
    TextLineEdit *txtBxFactoryContact;
    NumberLineEdit *txtBxFactoryEmployeeCount;

    QLabel *lblRecordingDateTime;
    QDateTimeEdit *dteRecordingBeginTime;
    QDateTimeEdit *dteRecordingEndTime;

};

#endif // METADATAVIEW_H
