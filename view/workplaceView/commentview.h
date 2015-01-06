#ifndef COMMENTVIEW_H
#define COMMENTVIEW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "textlineedit.h"
#include "textedit.h"

class CommentView : public QWidget
{
    Q_OBJECT
public:
    explicit CommentView(QWidget *parent = 0);
    ~CommentView();

    QString getProblemName() const;
    QString getProblemDescription() const;
    QString getMeasureName() const;
    QString getMeasureDescription() const;
    QString getWorkerPerception() const;

signals:
    void back();
    void save();

public slots:
    void setComment(const QString &problemName, const QString &problemDesc, const QString &measureName, const QString &measureDesc, const QString &workerPerception);

private slots:
    void btnBackClicked();

private:
    QLabel *lblViewName;
    QLabel *lblProblem;
    QLabel *lblProblemName;
    QLabel *lblProblemDescription;
    QLabel *lblMeasure;
    QLabel *lblMeasureName;
    QLabel *lblMeasureDescription;
    QLabel *lblWorkerPerception;
    QLabel *lblWorkerPerceptionDescription;

    TextLineEdit *txtBxProblemName;
    TextEdit *txtBxProblemDescription;
    TextLineEdit *txtBxMeasureName;
    TextEdit *txtBxMeasureDescription;
    TextEdit *txtBxPerceptionDescription;

    QPushButton *btnBack;
};

#endif // COMMENTVIEW_H
