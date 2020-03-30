#include "image_sender.h"
#include "QBuffer"

Image_Sender::Image_Sender(QTcpSocket *socket)
{
    this->mSocket=socket;
    this->isStop=true;
    //this->locker=
}

void Image_Sender::startSend()
{
    this->isStop=false;
    this->start();
}

void Image_Sender::setImage(const QImage &image)
{
    QBuffer *ibuff=new QBuffer(buffArray);
    image.save(ibuff,"JPEG");
}


