#ifndef LOADHANDLINGVIEW_H
#define LOADHANDLINGVIEW_H

#include <QLabel>
#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QGroupBox>
#include "valuecontrol.h"

/**
 * @brief A class providing a view for transporthandling. The class contains
 * different ValueControl for the type, of handling the weight to be handled,
 * the way to go and the hand used. Furthermore there is a TransportationListControl
 * with the list of transportations available.
 */
class LoadHandlingView : public QWidget
{
    Q_OBJECT

public:
    explicit LoadHandlingView(QWidget *parent = 0);
    ~LoadHandlingView();

    QString getGraspType() const;
    QString getHandlingType() const;
    int getWeight();
    int getDistance();

signals:

private slots:
    /**
     * @brief A slot that is called, whenever the type of handling changes.
     * Depending of the new type the ValueControl ranges of the weight
     * to be handled are adapted.
     * @param type The new type selected.
     */
    void setGraspType(const QString &graspType);
    void setHandlingType(const QString &handlingType);
    void setWeight(int &weight);
    void setDistance(int &distance);
    void typeChanged(QString type);

private:
    ValueControl *vlcGraspType;
    ValueControl *vlcHandlingType;
    ValueControl *vlcWeight;
    ValueControl *vlcDistance;
    QWidget *main;
    QWidget *control;

    const QVector<QString> graspValues =QVector<QString>()<<tr("Thumbcontact grasp")<<tr("Indexcontact grasp")<<tr("Handcontact grasp")<<tr("Thumb to 2 Fingers")<<tr("Fingergrasp")<<tr("Thumbindex")<<tr("Wrench")<<tr("Fullgrasp");
    const QVector<int> weightValues = QVector<int>()<<2<<3<<5<<10<<20;
    const QVector<int> heavyWeightValues = QVector<int>()<<100<<500<<1000<<1500<<2000;
    const QVector<int> distanceValues = QVector<int>()<<2<<3<<5<<10<<20;
    const QVector<QString> HandlingTypeValues = QVector<QString>()<<tr("holding")<<tr("replacing")<<tr("carrying")<<tr("pulling and pushing");
};

#endif // LoadHandlingView_H
