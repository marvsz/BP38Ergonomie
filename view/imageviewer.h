#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QWidget>
#include <QImage>
#include <QLabel>
#include <QPainter>

class ImageViewer : public QWidget
{
    Q_OBJECT
public:
    explicit ImageViewer(QWidget *parent = 0);

signals:

public slots:
    void setImage(const QImage &img);
    QString saveImage();

private:
    QImage image;
    QLabel *imgLabel;
};

#endif // IMAGEVIEWER_H
