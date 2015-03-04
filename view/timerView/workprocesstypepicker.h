#ifndef WORKPROCESSTYPEPICKER_H
#define WORKPROCESSTYPEPICKER_H

#include <QWidget>
#include "../selectablevaluebutton.h"
#include "../../enum.h"

class WorkProcessTypePicker : public QWidget
{
    Q_OBJECT
public:
    explicit WorkProcessTypePicker(QWidget *parent = 0);
    ~WorkProcessTypePicker();

    AVType getSelectedType() const;

signals:
    void selectedTypeChanged(AVType type);

public slots:
    void setSelectedType(AVType type);

private slots:
    void btnAVTypeClicked(int id);

private:
    SelectableValueButton *btnLeft;
    SelectableValueButton *btnRight;
    SelectableValueButton *btnBasic;

    AVType selectedType;

    SelectableValueButton* getBtnByType(AVType type);
    void setSelectedType(AVType type, bool emitSignal);
};

#endif // WORKPROCESSTYPEPICKER_H
