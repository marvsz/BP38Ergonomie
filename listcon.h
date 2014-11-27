#ifndef LISTCON_H
#define LISTCON_H

#include <QGroupBox>
#include <QLabel>
#include <QList>
#include <QString>
#include <QLineEdit>
#include "tool.h"
#include "textqpushbutton.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

class ListCon : public QGroupBox
{
    Q_OBJECT
public:
    explicit ListCon(QString name = "", QString opt1Name="", QString opt2Name="", QWidget *parent = 0);

signals:

public slots:
    void opt1TruePressed();
    void opt1FalsePressed();
    void opt2TruePressed();
    void opt2FalsePressed();
    void toolChanged(int id);
    void addTool();
    void opt1Changed();
    void opt2Changed();
    void setCurrentToolId(int id);
    void disableSelection();

private:
    int currentToolId;
    bool currOpt1;
    bool currOpt2;
    QLabel *name;
    QList<Tool*> tools;
    QLabel *newName;
    QLineEdit *newNameEdit;
    QLabel *opt1;
    QLabel *opt2;
    TextQPushButton *opt1TrueBtn;
    TextQPushButton *opt1FalseBtn;
    TextQPushButton *opt2TrueBtn;
    TextQPushButton *opt2FalseBtn;
    TextQPushButton *addBtn;
};

#endif // LISTCON_H
