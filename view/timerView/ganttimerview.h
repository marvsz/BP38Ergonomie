#ifndef GANTTIMERVIEW_H
#define GANTTIMERVIEW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QStringList>
#include "workprocessbutton.h"
#include "numberlineedit.h"
#include "iconconstants.h"

class GantTimerView : public QWidget
{
    Q_OBJECT
public:
    explicit GantTimerView(QWidget *parent = 0);
    ~GantTimerView();

signals:
    void workProcessSelected(int id, int type);
    void saveFrequenz(int id, int type);

public slots:
    void add(int id, int type, const QTime &start, const QTime &end);
    void clear();
    void setSelectedWorkProcess(int id, int type, int frequenz);

private slots:
    void btnZoomInClicked();
    void btnZoomOutClicked();
    void btnPlus();
    void btnMinus();

private:
    static const QStringList typePrefix;
    int secPixel;

    NumberLineEdit *numBxFrequenz;

    QPushButton *btnZoomIn;
    QPushButton *btnZoomOut;
    QPushButton *btnFrequenzPlus;
    QPushButton *btnFrequenzMinus;

    QHBoxLayout *leftWP;
    QHBoxLayout *rightWP;
    QHBoxLayout *basicWP;

    QVector<WorkProcessButton*> *leftWPBtns;
    QVector<WorkProcessButton*> *rightWPBtns;
    QVector<WorkProcessButton*> *basicWPBtns;

    QHBoxLayout* getLayout(int type);
    QVector<WorkProcessButton*>* getButtonVector(int type);
    void resizeClear();
};

#endif // GANTTIMERVIEW_H
