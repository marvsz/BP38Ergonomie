#ifndef LISTCON_H
#define LISTCON_H

#include <QGroupBox>
#include <QVector>
#include <QLabel>
#include <QList>
#include <QString>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "tool.h"
#include "selectablevaluebutton.h"


class ListCon : public QGroupBox
{
    Q_OBJECT
public:
    explicit ListCon(QString name = "", QVector<QString> *optionNames = NULL, QWidget *parent = 0);

signals:

public slots:

private slots:
    void setCurrentToolId(int id);
    void optionTruePressed(int index);
    void optionFalsePressed(int index);
    void optionChanged(int index);
    void toolChanged(int id);
    void addTool();
    void removeTool();
    void disableSelection();


private:
    int currentToolId;
    QVector<bool> currentOptions;
    QLabel *name;
    QList<Tool*>* tools;
    QLabel *newName;
    QLineEdit *newNameEdit;
    QVector<QLabel*> *options;
    QVector<SelectableValueButton*>* optionsTrueBtns;
    QVector<SelectableValueButton*>* optionsFalseBtns;
    SelectableValueButton *addBtn;
    SelectableValueButton *remBtn;
    bool isOptionChosen();
    Tool* toolWidthId(int id);
    int toolIndex(int toolId);
};

#endif // LISTCON_H
