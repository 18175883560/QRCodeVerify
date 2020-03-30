#ifndef CNI_FRAME_H
#define CNI_FRAME_H

#include<iostream>
#include<QByteArray>
#include<QTcpSocket>

class CNI_Frame
{
public:
    CNI_Frame();
    CNI_Frame(char frameType,QByteArray frameData);
    ~CNI_Frame();
    bool Send(QTcpSocket socket,bool endFlag);//发送数据
    bool recvData(QTcpSocket socket);
private:
    char _frameType;
    QByteArray data;
    int frameLength;
private:
    char getSumCheck(char *buff,int start,int length);//获取和校验
    bool isHeaderAvaliable(char *headerArray);//判断包头是否有效
//-----------------获取发送缓存-----------------------------------
    QByteArray getHeaderArray();//获取数据头
    QByteArray getSendBuff(bool endFlag);//获取发送缓存
};


union CNI_Frame_DataLength
{
    int dataLength;
    char buff[4];
};

#endif // CNI_FRAME_H
