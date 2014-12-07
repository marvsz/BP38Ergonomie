#ifndef MOREEXECUTIONCONDITION_H
#define MOREEXECUTIONCONDITION_H

#include <QWidget>
#include <QVBoxLayout>
#include <QFormLayout>

class MoreExecutionCondition : public QWidget
{
    Q_OBJECT
public:
    explicit MoreExecutionCondition(QWidget *parent = 0);

signals:

public slots:

private:
    QVBoxLayout *mainLayout;
    QFormLayout *mecLayout;
    QFormLayout *resultedMecLayout;

    QVector<QString*> *boolSelectionStrings;
    QVector<QString*> *noMiddleHighSelectionStrings;
    QVector<QString*> *noMiddleStrongSelectionStrings;
    QVector<QString*> *noLowHighSelectionStrings;


};

#endif // MOREEXECUTIONCONDITION_H
