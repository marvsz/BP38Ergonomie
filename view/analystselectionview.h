#ifndef ANALYSTSELECTIONVIEW_H
#define ANALYSTSELECTIONVIEW_H

#include <QPushButton>
#include <QWidget>
#include <QLabel>
#include <textlineedit.h>
#include <detailedlistitem.h>

class AnalystSelectionView : public QWidget
{
    Q_OBJECT
public:
    explicit AnalystSelectionView(QWidget *parent = 0);
    QString getAnalystLastName() const;
    QString getAnalystFirstName() const;
    QString getAnalystEmployer() const;
    QString getAnalystExperience() const;
    void add(int id, const QString &lastName, const QString &firstName);
    void clear();


signals:
    void forward();
    void create();
    void remove(int id);
    void select(int id);


private slots:
    void showCreateAnalyst();
    void dliPressed(int id);

private:
    QPushButton *btnCreateAnalyst;

    QLabel *lblAnalyst;
    QLabel *lblAnalystLastName;
    QLabel *lblAnalystFirstName;
    QLabel *lblAnalystEmployer;
    QLabel *lblAnalystExperience;

    TextLineEdit *txtBxAnalystLastName;
    TextLineEdit *txtBxAnalystFirstName;
    TextLineEdit *txtBxAnalystEmployer;
    TextLineEdit *txtBxAnalystExperience;

    QList<DetailedListItem*> *analysts;

    //QSpacerItem *spacer1; = new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Fixed);
    //QSpacerItem *spacer2; = new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Fixed);


};

#endif // ANALYSTSELECTIONVIEW_H
