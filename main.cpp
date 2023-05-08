#include <QCoreApplication>
#include "myudp.h"
#include "string"
#include "variables.h"
using namespace std;
int main(int argc, char *argv[])
{
 QCoreApplication a(argc, argv);
    string opcion = argv[2];
    MyUDP client;

    //cout<<"hola mundo \n";
    /* printf("esta es la opcion %s : \n",argv[2]);
    if(opcion == "--get_tiempo"){
        printf("obteniendo el tiempo del controlador %s : \n",argv[1]);
        socket.ReadData(O_CurrentTime);
    }else if(opcion == "--get_device_info"){
        printf("obteniendo las  informacion del dispositivo %s\n :",argv[1]);
        socket.ReadData(O_DeviceInfo);
    }else if(opcion == "--buscar_ips"){
        printf("obteniendo las ips del controlador ");
        socket.searchIps();
    }
*/

    //client.HelloUDP();
    //client.ReadData(O_CurrentTime);
    //client.ReadData(O_BasicInfo);
    //client.ReadData(O_DeviceInfo);
    client.ReadData(O_Schedule);
    return a.exec();
}
