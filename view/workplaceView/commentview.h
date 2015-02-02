#ifndef COMMENTVIEW_H
#define COMMENTVIEW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "textlineedit.h"
#include "textedit.h"
#include "../navigation/simplenavigateablewidget.h"

class CommentView : public SimpleNavigateableWidget
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

public slots:
    void setComment(const QString &problemName, const QString &problemDesc, const QString &measureName, const QString &measureDesc, const QString &workerPerception);

private:
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
};

#endif // COMMENTVIEW_H
