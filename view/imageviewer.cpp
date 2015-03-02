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

bool ImageViewer::saveImage(){
    QString timestamp = QDateTime::currentDateTime().toString("ddMMyyyy-HHmmss");
    return image.save(StandardPaths::writeableLocation().append("/img").append(timestamp).append(".png"), "PNG", 100);
}
