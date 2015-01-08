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

    const QVector<QString> boolSelectionStrings = QVector<QString>()<<tr("yes")<<tr("no");
    const QVector<QString> noMiddleHighSelectionStrings = QVector<QString>()<<tr("none")<<tr("medium")<<tr("high");
    const QVector<QString> noMiddleStrongSelectionStrings = QVector<QString>()<<tr("none")<<tr("medium")<<tr("strong");
    const QVector<QString> noLowHighSelectionStrings = QVector<QString>()<<tr("none")<<tr("minor")<<tr("high");
};

#endif // MOREEXECUTIONCONDITION_H
