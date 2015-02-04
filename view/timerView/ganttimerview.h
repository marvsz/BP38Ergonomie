#ifndef GANTTIMERVIEW_H
#define GANTTIMERVIEW_H

#include "../view/navigation/titledwidget.h"
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QStringList>
#include "workprocessbutton.h"
#include "numberlineedit.h"
#include "iconconstants.h"
#include "spaceritemtimer.h"
#include "../enum.h"

class GantTimerView : public TitledWidget
{
    Q_OBJECT
public:
    explicit GantTimerView(QWidget *parent = 0);
    ~GantTimerView();

    int getFrequenz() const;

signals:
    void workProcessSelected(int id, AVType type);
    void saveFrequenz();

public slots:
    void add(int id, AVType type, const QTime &start, const QTime &end);
    void setWorkProcessLists(QVector<QVariant> *leftWorkProcesses, QVector<QVariant> *rightWorkProcesses, QVector<QVariant> *basicWorkProcesses);
    void clear();
    void setSelectedWorkProcess(int id, AVType type, int frequenz);

private slots:
    void btnZoomInClicked();
    void btnZoomOutClicked();
    void btnPlus();
    void btnMinus();
    void btnWPLeftClicked(int id);
    void btnWPRightClicked(int id);
    void btnWPBasicClicked(int id);

private:
    int secPixel;
    int selWP_ID;
    AVType selWP_Type;

    NumberLineEdit *numBxFrequenz;

    QPushButton *btnZoomIn;
    QPushButton *btnZoomOut;
    QPushButton *btnFrequenzPlus;
    QPushButton *btnFrequenzMinus;

    QHBoxLayout *leftWP;
    QHBoxLayout *rightWP;
    QHBoxLayout *basicWP;

    QVector<QVariant> *leftWorkProcesses;
    QVector<QVariant> *rightWorkProcesses;
    QVector<QVariant> *basicWorkProcesses;

    QHBoxLayout* getLayout(int type);

    void resizeClear();
    void update();
};

#endif // GANTTIMERVIEW_H
