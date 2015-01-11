#ifndef SLIDERCONTROL_H
#define SLIDERCONTROL_H

#include <QWidget>
#include <QLabel>
#include <QSlider>
#include <QGridLayout>

class SliderControl : public QWidget
{
    Q_OBJECT
public:
    explicit SliderControl(QWidget *parent = 0);
    ~SliderControl();

    void setMinMax(int min, int max);
    void setInterval(int interval);
    int getValue() const;
    int getMin() const;
    int getMax() const;

signals:
    void valueChanged(int value);

public slots:
    void setValue(int value);

private slots:
    void sldrValueChanged(int value);

private:
    QLabel *lblMin;
    QLabel *lblMax;
    QLabel *lblValue;

    QSlider *sldrValue;
};

#endif // SLIDERCONTROL_H
