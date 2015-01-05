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

    QString getAnalystLastName() const;
    QString getAnalystFirstName() const;
    QString getAnalystEmployer() const;
    QString getAnalystExperience() const;

    QString getCorporationName() const;

    QString getFactoryName() const;
    QString getFactoryStreet() const;
    int getFactoryZip() const;
    QString getFactoryCity() const;
    QString getFactoryCountry() const;
    QString getFactoryContact() const;
    int getFactoryEmployeeCount() const;

    QDateTime getRecordTimeBegin() const;
    QDateTime getRecordTimeEnd() const;

signals:
    void showMainMenu();
    void saveMetaData();
    void showWorkplaceListView();

public slots:
    void setAnalyst(const QString &lastName, const QString &firstName, const QString &experience);
    void setEmployer(const QString &employer);
    void setCorporation(const QString &name);
    void setFactory(const QString &name, const QString &street, int zip, const QString &city, const QString &country, const QString &contact, int employeeCount);
    void setRecordTime(const QDateTime &begin, const QDateTime &end);

private slots:

    void backButtonClicked();
    void forwardButtonClicked();

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
    QLabel *lblFactoryZip;
    QLabel *lblFactoryCity;
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
    QDateTimeEdit *dteRecordingTimeBegin;
    QDateTimeEdit *dteRecordingTimeEnd;

};

#endif // METADATAVIEW_H
