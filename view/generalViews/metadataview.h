#ifndef METADATAVIEW_H
#define METADATAVIEW_H

#include "navigation/simplenavigateablewidget.h"
#include <QPushButton>
#include <QLabel>
#include <QDateTimeEdit>
#include "numberlineedit.h"
#include "datetimespinner.h"

class MetaDataView : public SimpleNavigateableWidget
{
    Q_OBJECT
public:
    explicit MetaDataView(QWidget *parent = 0);

    bool canGoForward() const{
        return true;
    }

    ViewType getForwardViewType() const{
        return ViewType::WORKPLACELIST_VIEW;
    }

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

public slots:
    void setEmployer(const QString &employer);
    void setCorporation(const QString &name);
    void setBranchOfIndustry(const QString &name, const QString &description);
    void setFactory(const QString &name, const QString &street, int zip, const QString &city, const QString &country, const QString &contact, int employeeCount);
    void setRecordTime(const QDateTime &begin, const QDateTime &end);


private:
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
