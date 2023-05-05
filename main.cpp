#include <QCoreApplication>
#include "myudp.h"
#include "variables.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyUDP socket;

    //client.HelloUDP();

    socket.ReadData(O_CurrentTime);
    socket.ReadData(O_DeviceInfo);
    return a.exec();
}
