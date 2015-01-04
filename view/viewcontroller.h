#ifndef VIEWCONTROLLER_H
#define VIEWCONTROLLER_H

#include <QStackedWidget>
#include "mainmenu.h"
#include "metadataview.h"
#include "documentationview.h"

class ViewController : public QStackedWidget
{
    Q_OBJECT
public:
    explicit ViewController(QWidget *parent = 0);

    static const int MAIN_MENU_VIEW = 0;
    static const int METADATA_VIEW = 1;
    static const int DOCUMENTATION_VIEW = 2;

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
    void saveMetaData();
    void updateMetaData();

public slots:
    void setMainMenuView();
    void setMetaDataView();
    void setDocumentationView();

    void setAnalyst(const QString &lastName, const QString &firstName, const QString &employer, const QString &experience);
    void setCorporation(const QString &name);
    void setFactory(const QString &name, const QString &street, int zip, const QString &city, const QString &country, const QString &contact, int employeeCount);
    void setRecordTime(const QDateTime &begin, const QDateTime &end);

private slots:
    void saveMetaDataRequested();

private:
    MainMenu *mainMenuView;
    MetaDataView *metaDataView;
    DocumentationView *documentationView;
};

#endif // VIEWCONTROLLER_H
