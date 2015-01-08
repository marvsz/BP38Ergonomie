#ifndef GENERALEXECUTIONCONDITION_H
#define GENERALEXECUTIONCONDITION_H

#include <QWidget>
#include <QGridLayout>
#include <QLineEdit>
#include "valuecontrol.h"

class GeneralExecutionCondition : public QWidget
{
    Q_OBJECT
public:
    explicit GeneralExecutionCondition(QWidget *parent = 0);

signals:

public slots:

private:
    QGridLayout *mainLayout;

    QLineEdit *txtbxDescription;
    ValueControl *valConMtmCode;

    const QVector<QString> mtmCodeTexts = QVector<QString>()<<tr("takeing/placing")<<tr("tool handling")<<tr("placing")<<tr("using")<<tr("body movement");
    const QVector<QString> mtmCodeValueTexts = QVector<QString>()<<tr("A")<<tr("H")<<tr("P")<<tr("B")<<tr("K");

};

#endif // GENERALEXECUTIONCONDITION_H
