// myudp.cpp

#include "myudp.h"
#include <string>
#include "variables.h"

MyUDP::MyUDP(QObject *parent) :
    QObject(parent)
{
    udpSocket = new QUdpSocket(this);
    quint16 Port = 13536;
    while(udpSocket->bind(QHostAddress::AnyIPv4, Port)==false) Port++;

    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(readPending()));
}
void MyUDP::ReadData(quint8 Object_id)
{
    if(netOpenFlag == true) return;
    gbtx[0] = frame_head;
    gbtx[1] = frame_ver;
    gbtx[2] = ID_PC;
    gbtx[3] = ID_TSC;
    gbtx[5] = Reserve_Data;
    gbtx[6] = Reserve_Data;
    gbtx[7] = areaNum;
    gbtx[10] = Reserve_Data;

    if(Object_id == O_CurrentTime)
    {

        gbtx[4] = DL_BasicInfo;
        gbtx[8] = OT_Query;
        gbtx[9] = O_CurrentTime;
        qDebug()<<"read time \n";
    }
    else if(Object_id == O_Schedule)
    {
        gbtx[4] = DL_CharacPar;
        gbtx[8] = OT_Query;
        gbtx[9] = O_Schedule;
        qDebug()<<"read Schedule";
    }
    else if(Object_id == O_Plan)
    {
        gbtx[4] = DL_CharacPar;
        gbtx[8] = OT_Query;
        gbtx[9] = O_Plan;
        qDebug()<<"read Plan";

    }
    else if(Object_id == O_Action)
    {
        gbtx[4] = DL_CharacPar;
        gbtx[8] = OT_Query;
        gbtx[9] = O_Action;
        qDebug()<<"read Action";
    }
    else if(Object_id == O_Pattern)
    {
        gbtx[4] = DL_CharacPar;
        gbtx[8] = OT_Query;
        gbtx[9] = O_Pattern;
        qDebug()<<"read Pattern";
    }
    else if(Object_id == O_Split)
    {
        gbtx[4] = DL_CharacPar;
        gbtx[8] = OT_Query;
        gbtx[9] = O_Split;
        qDebug()<<"read Split";
    }
    else if(Object_id == O_Sequence)
    {
        gbtx[4] = DL_CharacPar;
        gbtx[8] = OT_Query;
        gbtx[9] = O_Sequence;
        qDebug()<<"read Sequence";
    }
    else if(Object_id == O_Phase)
    {
        gbtx[4] = DL_CharacPar;
        gbtx[8] = OT_Query;
        gbtx[9] = O_Phase;
        qDebug()<<"read Phase";
    }
    else if(Object_id == O_Channel)
    {
        gbtx[4] = DL_CharacPar;
        gbtx[8] = OT_Query;
        gbtx[9] = O_Channel;
        qDebug()<<"read Channel";
    }
    else if(Object_id == O_Unit)
    {
        gbtx[4] = DL_CharacPar;
        gbtx[8] = OT_Query;
        gbtx[9] = O_Unit;
        qDebug()<<"read Unit";
    }
    else if(Object_id == O_Coord)
    {
        gbtx[4] = DL_CharacPar;
        gbtx[8] = OT_Query;
        gbtx[9] = O_Coord;
        qDebug()<<"read Coord";
    }
    else if(Object_id == O_Overlap)
    {
        gbtx[4] = DL_CharacPar;
        gbtx[8] = OT_Query;
        gbtx[9] = O_Overlap;
        qDebug()<<"read Overlap";
    }
    else if(Object_id == O_Peddet)
    {
        gbtx[4] = DL_Intervention;
        gbtx[8] = OT_Query;
        gbtx[9] = O_Peddet;
        qDebug()<<"read Peddet";
    }
    else if(Object_id == O_Vehdet)
    {
        gbtx[4] = DL_Intervention;
        gbtx[8] = OT_Query;
        gbtx[9] = O_Vehdet;
        qDebug()<<"read Vehdet";
    }
    else if(Object_id == O_PeddetState)
    {
        gbtx[4] = DL_Intervention;
        gbtx[8] = OT_Query;
        gbtx[9] = O_PeddetState;
        qDebug()<<"read PeddetState";
    }
    else if(Object_id == O_DeviceInfo)
    {
        gbtx[4] = DL_BasicInfo;
        gbtx[8] = OT_Query;
        gbtx[9] = O_DeviceInfo;
        qDebug()<<"read DeviceInfo";
    }
    else if(Object_id == O_BasicInfo)
    {
        gbtx[4] = DL_BasicInfo;
        gbtx[8] = OT_Query;
        gbtx[9] = O_BasicInfo;
        qDebug()<<"read BasicInfo";
    }
    else if(Object_id == O_WorkState)
    {
        gbtx[4] = DL_BasicInfo;
        gbtx[8] = OT_Query;
        gbtx[9] = O_WorkState;
        gbtx[10] = Reserve_Data;
        //este condicional es para recibir constantemente actualizaciones
        // if(ui->checkBox_AutoReportSignal->isChecked())
        //     gbtx[10] = 0x02;
        // else
        //     gbtx[10] = Reserve_Data;
        qDebug() <<"read WorkState";
    }

    quint8 CheckSumCalc = 0;
    for(quint8 i = 1; i<=10; i++)
    {
        CheckSumCalc += gbtx[i];
    }
    quint8 num = 11;
    if(CheckSumCalc == 0xC0)
    {
        gbtx[num++]= 0xDB;
        gbtx[num++]= 0xDC;
    }else if(CheckSumCalc == 0xDB){
        gbtx[num++]= 0xDB;
        gbtx[num++]= 0xDD;
    }else{
        gbtx[num++]= CheckSumCalc;
    }
    gbtx[num++]= frame_tail;

    AscPort = 161;
    AscIpStr = "192.168.1.122";

    QByteArray msg(QByteArray::fromRawData((const char *)gbtx, num));

    udpSocket->writeDatagram(msg, QHostAddress("192.168.1.122"), 161);


}
void MyUDP::HelloUDP()
{
    if(netOpenFlag == true) return;
    quint8 gbtx[32];
    gbtx[0] = frame_head;
    gbtx[1] = frame_ver;
    gbtx[2] = ID_PC;
    gbtx[3] = ID_TSC;
    gbtx[4] = DL_Com;
    gbtx[5] = areaNum;
    gbtx[6] = inteNumL;
    gbtx[7] = inteNumH;
    gbtx[8] = OT_Query;
    gbtx[9] = O_Call;
    gbtx[10] = Reserve_Data;

    quint8 CheckSumCalc = 0;
    for(quint8 i = 1; i<=10; i++)
    {
        CheckSumCalc += gbtx[i];
    }
    quint8 num = 11;
    if(CheckSumCalc == 0xC0)
    {
        gbtx[num++]= 0xDB;
        gbtx[num++]= 0xDC;
    }else if(CheckSumCalc == 0xDB){
        gbtx[num++]= 0xDB;
        gbtx[num++]= 0xDD;
    }else{
        gbtx[num++]= CheckSumCalc;
    }
    gbtx[num++]= frame_tail;



    AscPort = 161;
    QByteArray msg(QByteArray::fromRawData((const char *)gbtx, num));
    udpSocket->writeDatagram(msg, QHostAddress("255.255.255.255"), AscPort);
}


void MyUDP::readyRead()
{
    // when data comes in
    QByteArray buffer;
    buffer.resize(udpSocket->pendingDatagramSize());

    QHostAddress sender;
    quint16 senderPort;

    udpSocket->readDatagram(buffer.data(), buffer.size(),&sender, &senderPort);

    qDebug() << "Message from: " << sender.toString();
    qDebug() << "Message port: " << senderPort;
    qDebug() << "Message: " << buffer;

}

void MyUDP::readPending(){
    quint8 array[2048];
    QHostAddress sender;
    quint16 senderPort;
    quint16 size = udpSocket->bytesAvailable();
    qDebug()<<"hasta aca msg 3\n";
    if(size == 0)return;

    udpSocket->readDatagram((char *)array, size, &sender, &senderPort); //leer datos


    QString statusMsg;
    quint8 msgerror = Frame_right;
    quint16 dataEndPoint;
    quint8 CheckSumReceive,CheckSumCalc = 0;
    GBMSG_TYPE *gbmsg;
    gbmsg = (GBMSG_TYPE *)array;

    qDebug()<<"hasta aca msg 5\n";
    //Juzgando la estructura del marco de datos
    if(gbmsg->Head != frame_head || gbmsg->Version != frame_ver || gbmsg->Sendid != ID_TSC || \
            gbmsg->Reciveid != ID_PC || array[size-1] != frame_tail)
    {
        msgerror = Frame_wrong;
        qDebug()<<"error \n";
        return;
    }

    if(array[size-3] == 0xDB && array[size-2] == 0xDC)
    {
        dataEndPoint = size-4;
        CheckSumReceive = 0xC0;
        for(quint16 i=1;i<=dataEndPoint;i++)
        {
            CheckSumCalc += array[i];
        }
    }
    else if(array[size-3] == 0xDB && array[size-2] == 0xDD)
    {
        dataEndPoint = size-4;
        CheckSumReceive = 0xDB;
        for(quint16 i=1;i<=dataEndPoint;i++)
        {
            CheckSumCalc += array[i];
        }
    }
    else
    {
        dataEndPoint = size-3;
        CheckSumReceive = array[size-2];
        for(quint16 i=1;i<=dataEndPoint;i++)
        {
            CheckSumCalc += array[i];
        }
    }
    if(CheckSumCalc != CheckSumReceive)
    {
        msgerror = CheckSum_failed;
        qDebug()<<"Checksum fail";
        return;
    }
    quint16 rx_num = 0;
    for(quint16 num = 11; num <= dataEndPoint;)
    {
        if(array[num] == 0xDB && array[num+1] == 0xDC)
        {
            rx_var[rx_num++] = 0xC0;
            num += 2;
        }
        else if(array[num] == 0xDB && array[num+1] == 0xDD)
        {
            rx_var[rx_num++] = 0xDB;
            num += 2;
        }
        else
        {
            rx_var[rx_num++] = array[num];
            num ++;
        }
    }
    if(gbmsg->DataLinkCode == DL_BasicInfo)
    {

        if(gbmsg->ObjectCode == O_CurrentTime)//manipulación del tiempo
        {
            if(gbmsg->OperationType == OT_QueryAnswer)//respuesta de tiempo de consulta
            {
                //Consulta la hora con éxito, muestra la hora
                if(rx_num == 7)
                {
                    quint8 second = rx_var[0]/16*10 + rx_var[0]%16;//second
                    quint8 minute = rx_var[1]/16*10 + rx_var[1]%16;//minute
                    quint8 hour = rx_var[2]/16*10 + rx_var[2]%16;//hour
                    quint8 week = rx_var[3];//week
                    quint8 date = rx_var[4]/16*10 + rx_var[4]%16;//date
                    quint8 month = rx_var[5]/16*10 + rx_var[5]%16;//month
                    quint16 year = 2000 + rx_var[6]/16*10 + rx_var[6]%16;//year


                    qDebug()<<"read Time success: ";
                    qDebug()<<"segundos: ";
                    qDebug()<<second;
                    qDebug()<<"minutos: ";
                    qDebug()<<minute;
                    qDebug()<<"horas: ";
                    qDebug()<<hour;
                    qDebug()<<"semanas: ";
                    qDebug()<<week;
                }
            }

            else//Tipo de operación no compatible Tipo de operación no compatible
                msgerror = Unsupport_OT;
        }
        else if (gbmsg->ObjectCode == O_WorkState)
        {
            if (gbmsg->OperationType == OT_QueryAnswer) // respuesta de consulta de estado
            {

                qDebug() << tr("read WorkState success");
            }
            else if (gbmsg->OperationType == OT_InitiativeReport) // respuesta de consulta de estado
            {

                qDebug()<<tr("WorkState Report success");
            }
            // éxito de estado de consulta
            if (rx_num == 39)
            {
                //WorkState(rx_var);
            }
        }
        else if (gbmsg->ObjectCode == O_DeviceInfo)
        {
            if (gbmsg->OperationType == OT_QueryAnswer) // Respuesta de información del dispositivo de consulta
            {
                quint16 StrLen = 0;
                quint16 temp[64];
                for (quint16 i = 0; i < 128;)
                {
                    if (rx_var[i] != 0x00 || rx_var[i + 1] != 0x00)
                    {
                        temp[StrLen++] = (rx_var[i] << 8) | rx_var[i + 1];
                        i += 2;
                    }
                    else
                        break;
                }

                QString manufacturerInfoStr;
                manufacturerInfoStr.resize(StrLen);
                for (quint16 i = 0; i < StrLen; i++)
                {
                    manufacturerInfoStr[i] = QChar(temp[i]);
                }


                qDebug() << manufacturerInfoStr;


                memcpy(deviceInfoBuf, &rx_var[128], 48);
                QByteArray deviceversion;
                deviceversion.resize(4);

                for (quint8 i = 0; i < 4; i++)
                {
                    deviceversion[i] = rx_var[128 + i];
                }
                deviceversion = deviceversion.toHex();
                qDebug() << deviceversion;
                QByteArray deviceNumber;
                deviceNumber.resize(16);
                for (quint8 i = 0; i < 16; i++)
                {
                    deviceNumber[i] = rx_var[132 + i];
                }
                deviceNumber = deviceNumber.toHex();
                quint8 StrNum = deviceNumber.count();
                while (StrNum > 0)
                {
                    if (deviceNumber.at(0) == '0')
                        deviceNumber.remove(0, 1);
                    else
                        break;
                    StrNum = deviceNumber.count();
                }


                qDebug() << deviceNumber;
                QByteArray productionDate;
                productionDate.resize(6);
                for (quint8 i = 0; i < 6; i++)
                {
                    productionDate[i] = rx_var[148 + i];
                }
                productionDate = productionDate.toHex();

                qDebug() << productionDate;
                QByteArray configurationDate;
                configurationDate.resize(6);
                for (quint8 i = 0; i < 6; i++)
                {
                    configurationDate[i] = rx_var[154 + i];
                }
                configurationDate = configurationDate.toHex();

                qDebug() << configurationDate;
                //ReadFalg |= DevicePar; nose que hace esta linea

                qDebug() << tr("read DeviceInfo success");
            }
            else if (gbmsg->OperationType == OT_SetAnswer) // establecer tiempo de respuesta
            {


                qDebug() << tr("set DeviceInfo success");
            }
            else
                qDebug() << tr("Error");
        }
        else if(gbmsg->ObjectCode == O_BasicInfo)
        {
            if(gbmsg->OperationType == OT_QueryAnswer)//Respuesta de información del dispositivo de consulta
            {
                quint16 StrLen = 0;
                quint16 temp[64];
                for(quint16 i=0;i<128;)
                {
                    if(rx_var[i] != 0x00 || rx_var[i+1] != 0x00)
                    {
                        temp[StrLen++] = (rx_var[i]<<8)|rx_var[i+1];
                        i += 2;
                    }
                    else break;
                }

                QString InterInfoStr;
                InterInfoStr.resize(StrLen);
                for(quint16 i=0; i<StrLen; i++)
                {
                    InterInfoStr[i] = QChar(temp[i]);
                }

                for(int i=0;i<6;i++) mac[i] = rx_var[142+i];
                QByteArray mac_addr;
                mac_addr.resize(6);
                mac_addr[0] = rx_var[142];
                mac_addr[1] = rx_var[143];
                mac_addr[2] = rx_var[144];
                mac_addr[3] = rx_var[145];
                mac_addr[4] = rx_var[146];
                mac_addr[5] = rx_var[147];
                mac_addr = mac_addr.toHex();
                mac_addr.insert(10,":");
                mac_addr.insert(8,":");
                mac_addr.insert(6,":");
                mac_addr.insert(4,":");
                mac_addr.insert(2,":");
                qDebug()<<"la mac: "<<mac_addr;
                QString ip_target = tr("%1.%2.%3.%4").arg(rx_var[148]).arg(rx_var[149]).arg(rx_var[150]).arg(rx_var[151]);
                qDebug()<<"la Ip server: "<<ip_target;

                // ui->lineEdit_ServerIP->setText(tr("%1.%2.%3.%4").arg(rx_var[148]).arg(rx_var[149]).arg(rx_var[150]).arg(rx_var[151]));
                //ui->lineEdit_ServerPort->setText(tr("%1").arg((rx_var[152]<<8)|rx_var[153]));
                QString port_target = tr("%1").arg((rx_var[152]<<8)|rx_var[153]);
                qDebug()<<"El puerto: "<<port_target;

                double TimeZone = ((rx_var[156]<<16)|(rx_var[157]<<8)|rx_var[158])/3600.0;
                qDebug()<<"Time Zone: "<<TimeZone;
                if(rx_var[155]==0) TimeZone = TimeZone*(-1);


                quint32 TscNum = (rx_var[159]<<24)|(rx_var[160]<<16)|(rx_var[161]<<8)|rx_var[162];

                qDebug()<<tr("read BasicInfo success");
            }
            else if(gbmsg->OperationType == OT_SetAnswer)
            {
                //WriteFalg |= TimePar;

                qDebug()<<tr("set BasicInfo success");
            }
            else
                msgerror = Unsupport_OT;
        }
        else
        {
            msgerror = Unsupport_OB;
        }
    }
    else if(gbmsg->DataLinkCode == DL_Com)// esta  condicional nos devuelve las ips que estan disponibles para ello envia una trama broadcast
    {
        if(gbmsg->ObjectCode == O_Call && gbmsg->OperationType == OT_QueryAnswer)
        {
            QByteArray string;
            string.resize(4);
            for(quint8 i=0;i<4;i++) string[i] = rx_var[i];
            string = string.toHex();
            qDebug()<<"Version: "<<string;
            string.resize(2);
            for(quint8 i=0;i<2;i++) string[i] = rx_var[5 + i];
            string = string.toHex();

            qDebug()<<"Dispositivo: "<<string;

            QString senderIPStr = sender.toString();
            QString senderPortStr = tr("%1").arg(senderPort);
            qDebug()<<"Ip: "<<senderIPStr;
            qDebug()<<"Puerto In: "<<senderPort;

            QString out_port = tr("%1").arg(rx_var[4]);
            qDebug()<<"Puerto Out: "<<out_port;


            qDebug()<<tr("search success");
        }
    }
    else if(gbmsg->DataLinkCode == DL_CharacPar)
    {


        if(gbmsg->ObjectCode == O_Schedule)//Programación de operaciones de programación
               {
                   if(gbmsg->OperationType == OT_QueryAnswer)//respuesta de consulta
                   {
                       //búsqueda exitosa
                       quint8 ScheduleSize = 9;
                       for(quint16 i = 0; i < 5; i++)
                           {
                               quint16 readpoint = ScheduleSize * i + 1;
                               int number = rx_var[readpoint];
                               int month = rx_var[readpoint+1] | (rx_var[readpoint+2]<<8);
                               int day = rx_var[readpoint+3];
                               int date =  (quint32)rx_var[readpoint+4] | \
                                                              ((quint32)rx_var[readpoint+5]<<8) | \
                                                              ((quint32)rx_var[readpoint+6]<<16) | \
                                                              ((quint32)rx_var[readpoint+7]<<24);
                              int DayPlan = rx_var[readpoint+8];
                               qDebug()<<"Number: "<<number;
                               qDebug()<<"semana: "<<month;
                               qDebug()<<"dia: "<<day;
                               qDebug()<<"fecha: "<<date;


                           }
                           //ReadFalg |= SchedulePar;
                           //tableScheduleShowData();
                           //statusMsg = tr("Leer el plan de programación con éxito");
                           qDebug()<<tr("read Schedule success");
                       }
                   }
                   else if(gbmsg->OperationType == OT_SetAnswer)//establecer respuesta
                   {
                      // WriteFalg |= SchedulePar;
                       statusMsg = "Leer el plan de programación con éxito";
                       qDebug()<<tr("set Schedule success");
                   }
                   else{//Tipo de operación no compatible
                       msgerror = Unsupport_OT;
               }
        //desde aqui debemos agregar el codigo encargado de traernos las configuraciones del controlador
    }
    //termina la funcion
}
