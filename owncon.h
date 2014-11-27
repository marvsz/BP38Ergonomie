#ifndef OWNCON_H
#define OWNCON_H

#include <QWidget>
#include <QLineEdit>
#include <QSlider>
#include <QGroupBox>
#include <QVector>
#include <QString>
#include <QLabel>
#include <QHBoxLayout>
#include "ownqpushbutton.h"

class OwnCon : public QWidget
{
    Q_OBJECT
public:
    explicit OwnCon(QWidget *parent = 0);
    void setValues(int min, int max, QVector<int>* btnValues, QString* iconSetPath);
    void setText(QString text);
    QString getText() const;

signals:

public slots:

private slots:
    void txtBxAngleHasChanged();
    void sldrAngleHasChanged();
    void btnAngleHasClicked(int id);
    void btnPlusClicked();
    void btnMinusClicked();

private:
    int btnCount;
    int min;
    int max;
    QLineEdit *txtBxAngle;
    QSlider *sldrAngle;
    QPushButton *btnPlus;
    QPushButton *btnMinus;
    QLabel *lblText;
    QLabel *lblMin;
    QLabel *lblMax;
    QVector<OwnQPushButton*> *btnAngles;
    QHBoxLayout *btnLineLayout;

    void btnHighlight(int value);

};

#endif // OWNCON_H
