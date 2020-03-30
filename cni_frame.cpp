#include "cni_frame.h"
#include "iostream"
#include "QtEndian"

CNI_Frame::CNI_Frame()
{

}

CNI_Frame::CNI_Frame(char frameType, QByteArray frameData)
{
    _frameType=frameType;
    data=frameData;
}

bool CNI_Frame::Send(QTcpSocket socket, bool endFlag)
{
    QByteArray sendBuff=getSendBuff(endFlag);
    if(socket.write(sendBuff)<0)
        return false;
    else
        return true;
}

bool CNI_Frame::recvData(QTcpSocket socket)
{

}

//获取和校验
char CNI_Frame::getSumCheck(char *buff, int start, int length)
{
    char rtValue=0;
    for(int i=start; i<start+length; i++)
        rtValue+=buff[i];
    return rtValue ;
}
//判断包头是否有效
bool CNI_Frame::isHeaderAvaliable(char *headerArray)
{
    if(headerArray[0]==0x07 && headerArray[6]==0x07)
    {
        char sumCheck=getSumCheck(headerArray,0,7);//包头长度为8，有效长度7位+1位校验位
        if(sumCheck!=headerArray[7])
            return false;
        else
        {
            _frameType=headerArray[1];
            CNI_Frame_DataLength mLen;
            std::copy(headerArray+2,headerArray+5,mLen.buff);
            frameLength=mLen.dataLength;
            return true;
        }
    }
    else
    {
        return false;
    }
}

//获取待发送的数据头
QByteArray CNI_Frame::getHeaderArray()
{
    CNI_Frame_DataLength mLen;
    char headArray[8];
    headArray[0]=0x07;
    headArray[1]=_frameType;
    mLen.dataLength=data.size();
    std::copy(mLen.buff,mLen.buff+3,headArray+2);
    headArray[6]=0x07;
    headArray[7]=getSumCheck(headArray,0,7);
    return QByteArray(headArray,8);
}

//获取待发送的数据
QByteArray CNI_Frame::getSendBuff(bool endFlag)
{
    QByteArray header=getHeaderArray();
    char sumCheck=getSumCheck(data.data(),0,data.size());
    QByteArray rtArray;
    rtArray.append(header);
    rtArray.append(data);
    rtArray.append(sumCheck);
    if(endFlag)
    {
        char end[2]= {0x0d,0x0a};
        rtArray.append(end);
    }
    return rtArray;
}



