#ifndef UTILITYOPTION_H
#define UTILITYOPTION_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include "enum.h"
class UtilityOption : public QWidget
{
    Q_OBJECT
public:
    explicit UtilityOption(QString* name, UtilityOptionType optionType, QWidget *parent = 0);

    QString getTextValue();
    int getIntValue();
    void setValue(int i);
    void setValue(QString text);
    void clear();
    void setPlaceholder(QString placeholder);

signals:
    void valueChanged(int value);
    void valueChanged(QString text);

private slots:
    void textChanged();

private:
    QLabel* nameLabel;
    QLineEdit* inputTextField;
    UtilityOptionType optionType;
};

#endif // UTILITYOPTION_H
