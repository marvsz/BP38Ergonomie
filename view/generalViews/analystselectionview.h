#ifndef ANALYSTSELECTIONVIEW_H
#define ANALYSTSELECTIONVIEW_H

#include <QPushButton>
#include "../navigation/simplenavigateablewidget.h"
#include <QLabel>
#include <QVBoxLayout>
#include "../textlineedit.h"
#include "../detailedlistitem.h"
#include <QScrollArea>

class AnalystSelectionView : public SimpleNavigateableWidget
{
    Q_OBJECT
public:
    explicit AnalystSelectionView(QWidget *parent = 0);
    QString getAnalystLastName() const;
    QString getAnalystFirstName() const;
    QString getAnalystEmployer() const;
    QString getAnalystExperience() const;

    bool canGoBack() const{
        return false;
    }

    bool hasAdditionalNavigation() const{
        return true;
    }

    QList<QAbstractButton*> * getAdditionalNavigation() const;

signals:
    void remove(int id);
    void select(int id);

public slots:
    void add(int id, const QString &lastName, const QString &firstName);
    void clear();

private slots:
    void dliPressed(int id);
    void btnCreateAnalystClicked();

private:
    QPushButton *btnCreateAnalyst;

    QVBoxLayout *listContentLayout;
    QScrollArea *scAnalysts;

};

#endif // ANALYSTSELECTIONVIEW_H
