#ifndef OPTIONSELECTIONCONTROL_H
#define OPTIONSELECTIONCONTROL_H

#include <QWidget>
#include <QHBoxLayout>
#include <QStringList>
#include <QVariant>
#include "selectablevaluebutton.h"

class OptionSelectionControl : public QWidget
{
    Q_OBJECT
public:
    explicit OptionSelectionControl(QWidget *parent = 0);

    QVariant getSelectedValue() const;
    QString getSelectedTexts() const;
    int getSelectedID() const;

signals:
    void selectionChanged(int id);

public slots:
    void setSelectedValue(int id);
    void setSelectedValue(const QString &text);
    void setSelectedByValue(int value);
    void setValues(const QStringList &texts, const QVector<QVariant> &values);
    void setValues(const QStringList &texts);

private:
    SelectableValueButton *currentSelectedBtn;

    QVector<SelectableValueButton*> btnOptions;
    QHBoxLayout *mainLayout;

    void clear();

};

#endif // OPTIONSELECTIONCONTROL_H
