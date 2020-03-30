#include "QTcpSocket"
#include "QThread"
#include "QImage"
#include "QReadWriteLock"

#ifndef IMAGE_SENDER_H
#define IMAGE_SENDER_H


class Image_Sender:public QThread
{
private:
    //需要发送的图像
    QByteArray *buffArray;
    //是否停止线程
    bool isStop;
    //线程互斥锁，防止线程在发送，赋值图像时冲突
    QReadWriteLock *locker;

    QTcpSocket *mSocket;
private slots:
    void on_socket_error(QAbstractSocket::SocketError err);
    void on_socket_disconnect();
public:
    Image_Sender(QTcpSocket *socket);
    ~Image_Sender();
    void startSend();
    void stop();
    void setImage(const QImage &image);
protected:
    void run() override;
};



//协议头结构体
struct frame_header_struct
{
    char startFlag;
    ushort flag;
    int dataLength;
    char endFlag;
    char sumCheck;
    bool isVaildHeader()
    {
        if(startFlag==endFlag && startFlag==0x07)
        {
            int cal_sum=startFlag+flag+dataLength+endFlag;
            if((char)cal_sum==sumCheck)
                return true;
            else
                return false;
        }
        else
            return false;
    }
} ;
//协议头联合体
union frame_header_array
{
    frame_header_struct frameHeader;
    char array[9];
};


#endif // IMAGE_SENDER_H
