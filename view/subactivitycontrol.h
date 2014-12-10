#ifndef SUBACTIVITYCONTROL_H
#define SUBACTIVITYCONTROL_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include "selectablevaluebutton.h"

class SubActivityControl : public QWidget
{
    Q_OBJECT
public:
    explicit SubActivityControl(QWidget *parent = 0);

signals:

public slots:

private slots:
    void addSubActivity();
    void deleteSubActivity();
    void subActivitySelected(int id);

private:
    QPushButton *btnAdd;
    QPushButton *btnDelete;
    QLineEdit *txtbxDescription;
    QVector<SelectableValueButton*> *btnList;
    QVBoxLayout *btnListLayout;

    SelectableValueButton *selectedBtn;

};

#endif // SUBACTIVITYCONTROL_H
