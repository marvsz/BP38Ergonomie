#ifndef METADATAVIEW_H
#define METADATAVIEW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QDateTimeEdit>
#include "numberlineedit.h"
#include "datetimespinner.h"

class MetaDataView : public QWidget
{
    Q_OBJECT
public:
    explicit MetaDataView(QWidget *parent = 0);


    QString getCorporationName() const;

    QString getBranchOfIndustryName() const;
    QString getBranchOfIndustryDescription() const;

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
    void back();
    void save();
    void forward();

public slots:
    void setEmployer(const QString &employer);
    void setCorporation(const QString &name);
    void setBranchOfIndustry(const QString &name, const QString &description);
    void setFactory(const QString &name, const QString &street, int zip, const QString &city, const QString &country, const QString &contact, int employeeCount);
    void setRecordTime(const QDateTime &begin, const QDateTime &end);

private slots:
    void backButtonClicked();
    void forwardButtonClicked();

private:

    QPushButton *btnBack;
    QPushButton *btnCancel;
    QPushButton *btnSave;

    QLabel *lblViewDescription;
    QPushButton *btnForward;

    TextLineEdit *txtBxAnalystLastName;
    TextLineEdit *txtBxAnalystFirstName;
    TextLineEdit *txtBxAnalystEmployer;
    TextLineEdit *txtBxAnalystExperience;

    QLabel *lblCorporation;
    QLabel *lblCorpName;
    TextLineEdit *txtBxCorpName;

    QLabel *lblBranchOfIndustry;
    QLabel *lblBoIName;
    TextLineEdit *txtBxBoIName;
    QLabel *lblBoIDescription;
    TextLineEdit *txtBxBoIDescription;

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
    QLabel *lblRecordingDateTimeBegin;
    QLabel *lblRecordingDateTimeEnd;
    DateTimeSpinner *dteRecordingTimeBegin;
    DateTimeSpinner *dteRecordingTimeEnd;

};

#endif // METADATAVIEW_H
