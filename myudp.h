// myudp.h

#ifndef MYUDP_H
#define MYUDP_H
#include "variables.h"
#include <QObject>
#include <QUdpSocket>
#include <iostream>

class MyUDP : public QObject
{
    Q_OBJECT
public:
    explicit MyUDP(QObject *parent = 0);
    void HelloUDP();
    void ReadData(quint8 Object_id);


signals:

public slots:
    void readyRead();
    void readPending();

private:

    QUdpSocket    *udpSocket;
    QMetaObject::Connection udpcon;
    quint8 gbtx[2048];
    quint8 temp_var[2048];
    quint8 rx_var[2048];
    quint8 deviceInfoBuf[48];
    quint8 mac[6];

    QString RemoteIPAddressStr;
    quint16 RemotePort;

    bool netOpenFlag = false;

    quint8 areaNum;
    quint8 inteNumL;
    quint8 inteNumH;
    quint8 OnLineCount;
    quint16 AscPort;
    QString AscIpStr;
    typedef struct
    {
        quint8 Head;
        quint8 Version;
        quint8 Sendid;
        quint8 Reciveid;

        quint8 DataLinkCode;
        quint8 AreaNum;
        quint8 IntersectionH;
        quint8 IntersectionL;

        quint8 OperationType;
        quint8 ObjectCode;
        quint8 Reserve;
    }GBMSG_TYPE;

};



#endif // MYUDP_H
