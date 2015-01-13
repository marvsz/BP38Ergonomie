#ifndef ANALYSTSELECTIONVIEW_H
#define ANALYSTSELECTIONVIEW_H

#include <QPushButton>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
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

signals:
    void forward();
    void create();
    void remove(int id);
    void select(int id);

public slots:
    void add(int id, const QString &lastName, const QString &firstName);
    void clear();

private slots:
    void btnMinimizeClicked();
    void btnMaximizeClicked();
    void dliPressed(int id);
    void btnCreateAnalystClicked();

private:

    bool status;
    QPushButton *btnMaximize;
    QPushButton *btnMinimize;
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

    QWidget *createAnalyst;
    QVBoxLayout *listContentLayout;

};

#endif // ANALYSTSELECTIONVIEW_H
