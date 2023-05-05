#include <QCoreApplication>
#include "myudp.h"
#include "string"
#include "variables.h"
using namespace std;
int main(int argc, char *argv[])
{

    string opcion = argv[2];
    MyUDP socket;
    cout<<"hola mundo";
    printf("esta es la opcion %s : \n",argv[2]);
    if(opcion == "--get_fases"){
            printf("obteniendo fases del controlador %s : \n",argv[1]);

       }else if(opcion == "--get_secuencias"){
            printf("obteniendo las secuencias del controlador %s\n :",argv[1]);
       }
    //client.HelloUDP();
    //socket.ReadData(O_CurrentTime);
    //socket.ReadData(O_DeviceInfo);

}
