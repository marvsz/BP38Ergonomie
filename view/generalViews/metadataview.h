#ifndef METADATAVIEW_H
#define METADATAVIEW_H

#include "../navigation/simplenavigateablewidget.h"
#include <QPushButton>
#include <QLabel>
#include <QDateTimeEdit>
#include "../numberlineedit.h"
#include "../datetimespinner.h"
#include "../interfaces/irecording.h"
#include "../interfaces/ifactory.h"
#include "../interfaces/icoperation.h"
#include "../interfaces/ibranchofindustry.h"
#include "../../databaseHandler/dbconstants.h"

class MetaDataView : public SimpleNavigateableWidget, IRecording, IFactory, ICorperation, IBranchOfIndustry
{
    Q_OBJECT
    Q_INTERFACES(IRecording)
    Q_INTERFACES(IFactory)
    Q_INTERFACES(ICorperation)
    Q_INTERFACES(IBranchOfIndustry)
public:
    explicit MetaDataView(QWidget *parent = 0);

    bool canGoForward() const{
        return true;
    }

    ViewType getForwardViewType() const{
        return ViewType::WORKPLACELIST_VIEW;
    }

signals:
    void saveRecording(QHash<QString, QVariant> values);
    void saveFactory(QHash<QString, QVariant> values);
    void saveCorperation(QHash<QString, QVariant> values);
    void saveBranchOfIndustry(QHash<QString, QVariant> values);

public slots:
    void setRecording(QHash<QString, QVariant> values);
    void setFactory(QHash<QString, QVariant> values);
    void setCorperation(QHash<QString, QVariant> values);
    void setBranchOfIndustry(QHash<QString, QVariant> values);

    void onLeaving();

private slots:
    void validateEndTime();

private:
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
