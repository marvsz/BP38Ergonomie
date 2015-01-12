#ifndef ANALYSTSELECTIONVIEW_H
#define ANALYSTSELECTIONVIEW_H

#include <QPushButton>
#include <QWidget>
#include <QLabel>
#include <textlineedit.h>

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
    void setAnalyst(const QString &lastName, const QString &firstName, const QString &experience);
    void setEmployer(const QString &employer);

private slots:
    void showCreateAnalyst();

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


};

#endif // ANALYSTSELECTIONVIEW_H
