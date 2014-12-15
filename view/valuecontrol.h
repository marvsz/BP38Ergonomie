#ifndef ValueControl_H
#define ValueControl_H

#include <QWidget>
#include <QLineEdit>
#include <QSlider>
#include <QVector>
#include <QString>
#include <QLabel>
#include <QHBoxLayout>
#include "selectablevaluebutton.h"
#include "enum.h"

class ValueControl : public QWidget
{
    Q_OBJECT
public:
    explicit ValueControl(VariantControl controlType, QWidget *parent = 0);

    void setValues(int min, int max, QVector<int>* btnValues, QString* iconSetPath);
    void setValues(QVector<QString*> *btnTexts, QVector<QString *> *btnTextValues, QString* iconSetPath);

    VariantControl getControlType() const;

    void setText(QString text);
    QString getText() const;

    void setTextHint(const QString &text);

    void setUnit(const QString &unit);
    QString getUnit() const;

    QString getTextValue() const;
    int getValue() const;


signals:
    void valueChanged(int value);
    void valueChanged(QString text);

public slots:
    void setValue(int value);

private slots:
    void txtBxValueHasChanged();
    void sldrValueHasChanged();
    void btnValueHasClicked(int id);
    void btnTextHasClicked(int id);
    void btnPlusClicked();
    void btnMinusClicked();
    void txtChanged(QString value);

private:
    QVector<int> *btnRanges;
    QVector<QString*> *btnTextValues;
    QString unit;
    int currentSelectedBtnID;
    VariantControl conType;

    QLineEdit *txtBxValue;
    QSlider *sldrValue;
    QPushButton *btnPlus;
    QPushButton *btnMinus;
    QLabel *lblText;
    QLabel *lblMin;
    QLabel *lblMax;
    QVector<SelectableValueButton*> *btnValues;
    QHBoxLayout *btnLineLayout;

    void btnHighlight(int value);

};

#endif // ValueControl_H
