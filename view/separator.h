#ifndef SEPARATOR_H
#define SEPARATOR_H

#include <QWidget>

/**
 * @brief The Separator class represents a separator line, which is actually a optical delimination for gui objects.
 * The Separator has a orientation and a fixed thickness.
 * Note: You can not change the orientation or thickness of a Separator afterwards.
 */
class Separator : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief Separator Creates a new Separator with the given orientation and thickness. Default orientation
     * is horizontal and default thickness is 3.
     * @param orientation The orientation of the seperator, either it is horizontal or vertical
     * @param thickness Fixed thickness of the seperator in pixel
     * @param parent The parent object of the seperator
     */
    explicit Separator(Qt::Orientation orientation = Qt::Horizontal, int thickness  = 3, QWidget *parent = 0);
    ~Separator();

private:
    void paintEvent(QPaintEvent *event);

};

#endif // SEPARATOR_H
