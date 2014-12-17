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

    QVector<QString*> *mtmCodeTexts;
    QVector<QString*> *mtmCodeValueTexts;

};

#endif // GENERALEXECUTIONCONDITION_H
