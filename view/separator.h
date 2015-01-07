#ifndef SEPARATOR_H
#define SEPARATOR_H

#include <QFrame>

class Separator : public QFrame
{
    Q_OBJECT
public:
    /**
     * @brief Separator A seperator line, which is actually a optical delimination for gui objects
     * @param orientation The orientation of the seperator, either it is horizontal or vertical
     * @param thickness Fixed thickness of the seperator
     * @param parent The parent object of the seperator
     */
    explicit Separator(Qt::Orientation orientation, int thickness, QWidget *parent = 0);

signals:

public slots:

};

#endif // SEPARATOR_H
