#ifndef ValueControl_H
#define ValueControl_H

#include <QWidget>
#include <QLineEdit>
#include <QSlider>
#include <QVector>
#include <QString>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include "selectablevaluebutton.h"
#include "../enum.h"

class ValueControl : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief ValueControl Creates a new Value Control
     * @param controlType Type of the value Control, remember you can not change the type
     * @param parent Parent widget which holds the value control or if 0 then a standalone window
     */
    explicit ValueControl(ValueControlType controlType, QWidget *parent = 0);

    /**
     * @brief setValues Sets the values of the control, is only appliable if the control type is VALUE_CONTROL
     * @param min Minimum value
     * @param max Maximum value
     * @param btnValues The predefinied values for the Buttons, there will be shown as many buttons as the length of the vector
     * @param iconSetPath The path to the icons, the names of the icons muss be the values in btnValues and the filetype png
     */
    void setValues(int min, int max, const QVector<int> &btnValues, const QString &iconSetPath);

    /**
     * @brief setValues Sets the values of the control, is only appliable if the control type is TEXT_CONTROL
     * @param btnTexts The predefinied texts for the buttons, there will be shown as many buttons as the length of the vector
     * @param btnTextValues The predefinied text values for a button, if a button gets selected this is the text that will be shown in the QLineEdit
     * @param iconSetPath The path to the icons, the names of the icons muss be the texts in btnTexts and the filetype png
     */
    void setValues(bool showText, const QVector<QString> &btnTexts, const QVector<QString> &btnTextValues, const QString &iconSetPath);

    /**
     * @brief getControlType Returns the type of the control, which is applied the instantiation
     * @return the control type
     */
    ValueControlType getControlType() const;

    /**
     * @brief setText Sets the description label of the control
     * @param text the text to be set, note that the displayed text is: "text [unit]:" if and only if unit is set otherwise
     * it is: "text:"
     */
    void setText(const QString &text);

    /**
     * @brief getText returns the description text of the control
     * @return the text which was set with setText, not the actually displayed text in the control
     */
    QString getText() const;

    /**
     * @brief setTextHint Sets a text placeholder for the TextLineEdit, note only appliable if control type is TEXT_CONTROL
     * @param text The placeholder text
     */
    void setTextHint(const QString &text);

    /**
     * @brief setUnit The unit that will be displayed in the control description and on the buttons after the value, only appliable if control type is VALUE_CONTROL
     * @param unit the unit of the values
     */
    void setUnit(const QString &unit);

    /**
     * @brief getUnit returns the set unit
     * @return returns the unit if the unit was not set than the emtpy QString
     */
    QString getUnit() const;

    /**
     * @brief getTextValue Is only appliable if the control type
     * @return
     */
    QString getTextValue() const;
    int getValue() const;


signals:
    void valueChanged(int value);
    void valueChanged(const QString &text);
    void valueChanged(const QVariant &value);

public slots:
    void setValue(int value);
    void setValue(const QString &text);

private slots:
    void txtBxValueHasChanged();
    void sldrValueHasChanged();
    void btnValueHasClicked(int id);
    void btnTextHasClicked(int id);
    void btnPlusClicked();
    void btnMinusClicked();
    void txtChanged(const QString &value);

private:
    QVector<int> *btnRanges;
    QVector<QString> btnTextValues;
    QString unit;
    int currentSelectedBtnID;
    int emitChangeValue;
    int min;
    int max;
    ValueControlType conType;

    QLineEdit *txtBxValue;
    QSlider *sldrValue;
    QPushButton *btnPlus;
    QPushButton *btnMinus;
    QLabel *lblText;
    QLabel *lblMin;
    QLabel *lblMax;
    QVector<SelectableValueButton*> *btnList;
    QHBoxLayout *btnLineLayout;

    void btnHighlight(int value);

};

#endif // ValueControl_H
