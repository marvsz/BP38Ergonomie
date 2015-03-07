#ifndef COMMENTVIEW_H
#define COMMENTVIEW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "../textlineedit.h"
#include "../textedit.h"
#include "../navigation/simplenavigateablewidget.h"
#include "../interfaces/icomment.h"
#include "../../databaseHandler/dbconstants.h"

class CommentView : public SimpleNavigateableWidget, IComment
{
    Q_OBJECT
    Q_INTERFACES(IComment)
public:
    explicit CommentView(QWidget *parent = 0);
    ~CommentView();

signals:
    void saveComment(QHash<QString, QVariant> values);

public slots:
    void setComment(QHash<QString, QVariant> values);
    void onLeaving();

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
