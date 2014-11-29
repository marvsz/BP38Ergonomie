#ifndef SEPERATOR_H
#define SEPERATOR_H

#include <QWidget>
#include <QFrame>

class Seperator : public QFrame
{
    Q_OBJECT
public:
    /**
     * @brief Seperator A seperator line, which is actually a optical delimination for gui objects
     * @param orientation The orientation of the seperator, either it is horizontal or vertical
     * @param thickness Fixed thickness of the seperator
     * @param parent The parent object of the seperator
     */
    explicit Seperator(Qt::Orientation orientation, int thickness, QWidget *parent = 0);

signals:

public slots:

};

#endif // SEPERATOR_H
