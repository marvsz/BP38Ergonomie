#include "imageviewer.h"
#include <QDebug>
#include <QVBoxLayout>
#include "../standardpaths.h"
#include <QDateTime>

ImageViewer::ImageViewer(QWidget *parent) :
    QWidget(parent),
    imgLabel(new QLabel(this))
{

    imgLabel->setPixmap(QPixmap::fromImage(image));
    imgLabel->setAlignment(Qt::AlignCenter);
}

void ImageViewer::setImage(const QImage &img){
    this->image = img;
    imgLabel->setPixmap(QPixmap::fromImage(img));
    if(this->image.size() != size()){
        setFixedSize(this->image.size());
        imgLabel->setFixedSize(this->image.size());
    }
    update();
}

QString ImageViewer::saveImage(){
    QString timestamp = QDateTime::currentDateTime().toString("dd-MM-yy-hh-mm-ss");
    QString filePath = QString("%1%2%3%4").arg(StandardPaths::writeableLocation()).arg("/img-").arg(timestamp).arg(".png");
    if(image.save(filePath, "PNG", 100))
        return filePath;
    else
        qDebug() << "Image could not be saved!";
        return NULL;
}
