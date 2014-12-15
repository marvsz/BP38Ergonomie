#ifndef UTILITYOPTION_H
#define UTILITYOPTION_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include "enum.h"

/**
 * @brief A class prividing functionality for an option of a utility which is a QWidget
 * containing a special textfield NumberLineEdit or TextLineEdit, depending on the type.
 */
class UtilityOption : public QWidget
{
    Q_OBJECT
public:
    explicit UtilityOption(UtilityOptionType optionType, QWidget *parent = 0);

    QString getTextValue();
    int getIntValue();
    void setValue(int i);
    void setValue(QString text);
    void clear();
    void setPlaceholder(QString placeholder);

    void setMinimumHeight(int minh);
    void setMinimumWidth(int minw);
    void setMinimumSize(int minw, int minh);
    void setMaximumHeight(int maxh);
    void setMaximumWidth(int maxw);
    void setMaximumSize(int maxw, int maxh);

signals:
    void valueChanged(int value);
    void valueChanged(QString text);

private slots:
    void textChanged();

private:
    QLineEdit* inputTextField;
    UtilityOptionType optionType;
};

#endif // UTILITYOPTION_H
