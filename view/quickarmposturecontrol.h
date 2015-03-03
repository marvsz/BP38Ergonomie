#ifndef QUICKARMPOSTURECONTROL_H
#define QUICKARMPOSTURECONTROL_H

#include <QWidget>
#include <QVBoxLayout>
#include <QStringList>
#include <QVariant>
#include "selectablevaluebutton.h"
#include <QString>

class QuickArmPostureControl : public QWidget
{ Q_OBJECT
public:
    explicit QuickArmPostureControl(QWidget *parent=0);

    QVariant getSelectedValue() const;
    QString getSelectedTexts() const;
    int getSelectedID() const;

signals:
    void selectionChanged(int id);
    void specificationChanged(int id);

public slots:
    void setSelectedValue(int id);
    void setSelectedSpecification(int id);
    //void setSelectedLeft(int id);
    //void setSelectedRight(int id);
    void setSelectedValue(const QString &text);
    void setSelectedByValue(int value);
    void setValues(const QStringList &texts, const QVector<QVariant> &values);
    void setValues(const QStringList &texts);
    void setValues(const QStringList &texts, const QStringList &differ, const QString &label);

private:
    SelectableValueButton *currentSelectedBtn;
    //SelectableValueButton *currentLeftBtn;
    //SelectableValueButton *currentRightBtn;
    SelectableValueButton *currentSpeciBtn;

    QVector<SelectableValueButton*> btnOptions;
    //QVector<SelectableValueButton*> leftOptions;
    //QVector<SelectableValueButton*> rightOptions;
    QVector<SelectableValueButton*> speciOptions;
    QVBoxLayout *mainLayout;

    void clear();

    int id;
    int idSpeci;
    //int idLeft;
    //int idRight;

};


#endif // QUICKARMPOSTURECONTROL_H
