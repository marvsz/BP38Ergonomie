#ifndef VERTICALOPTIONSELECTIONCONTROL_H
#define VERTICALOPTIONSELECTIONCONTROL_H

#include <QWidget>
#include <QVBoxLayout>
#include <QStringList>
#include <QVariant>
#include "selectablevaluebutton.h"
#include <QString>

class VerticalOptionSelectionControl : public QWidget
{
    Q_OBJECT
public:
    explicit VerticalOptionSelectionControl(QWidget *parent=0);

    QVariant getSelectedValue() const;
    QString getSelectedTexts() const;
    int getSelectedID() const;

signals:
    void selectionChanged(int id);

public slots:
    void setSelectedValue(int id);
    void setValues(const QStringList &texts, const QString &label);

private:
    SelectableValueButton *currentSelectedBtn;

    QVector<SelectableValueButton*> btnOptions;
    QVBoxLayout *mainLayout;

    void clear();
    int id;

};

#endif // VERTICALOPTIONSELECTIONCONTROL_H
