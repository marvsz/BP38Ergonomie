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

    const QVector<QString> boolSelectionStrings = QVector<QString>()<<"Ja"<<"Nein";
    const QVector<QString> noMiddleHighSelectionStrings = QVector<QString>()<<"keine"<<"mittlere"<<"hohe";
    const QVector<QString> noMiddleStrongSelectionStrings = QVector<QString>()<<"keine"<<"mittlere"<<"starke";
    const QVector<QString> noLowHighSelectionStrings = QVector<QString>()<<"keine"<<"geringe"<<"hohe";
};

#endif // MOREEXECUTIONCONDITION_H
