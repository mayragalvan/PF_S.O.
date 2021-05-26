// MPISO.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*----------------------------------- EJEMPLO PROGRAMA MPI SIN BLOQUEO PARA SERVIDORES ---------------------------------------*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <mpi.h> // Librería para MPI.
#include <WinSock2.h>  //Librería para conexión de sockets.

using namespace std;


//Función main () contiene el número de argumentos de la línea de comandos.
int main(int argc, char** argv) // Números de argumentos y vector de argumentos.
{
    int size; // Número total de procesos.
    int rank; // El rank assignado al proceso de comunicación.
    char name[80]; // Maquina donde corren los procesos.
    int length; // Variable para longitud de la palabra del modelo de maquina.

    WSADATA WSAData; //Se crea el objeto de la estructura WSADATA que contiene la información de la implementación de sockets en Windows, 
   //se asegura que el sistema soporte Winsock2.
    SOCKET server, client; //Variables tipo de socket para la conexión
    SOCKADDR_IN serverAddr, clientAddr;

    WSAStartup(MAKEWORD(2, 0), &WSAData);
    server = socket(AF_INET, SOCK_STREAM, 0);

    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(5555);
    bind(server, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
    listen(server, 0);


    /*Inicialización de la ejecución de MPI y su ambiente*/
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // (MPI_COMM_WORLD) es la comunicación por Default de MPI :: Número de rango del proceso actual.
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Número de procesos ejecutados en el grupo default.
    MPI_Get_processor_name(name, &length); // Nombre del dispositivo conectado.


    int send_data = rank + 100;
    MPI_Request send_request;
    MPI_Isend(&send_data, 1, MPI_INT, (rank + 1) % size, 1, MPI_COMM_WORLD, &send_request); // MPI solicita enviar el dato al target con el mensaje 
    //y la solicitud se almacena en el request de envío. La función esta preparando la ejecución y se ejecuta cuando ambos proceos están listos para sincronizarse.
    int recv_data;
    MPI_Recv(&recv_data, 1, MPI_INT, (rank + size - 1) % size, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE); // La función que completa la petición al recibirla y pasa a la que sigue.
    cout <<"Proceso" << rank << "recibe" << recv_data << endl; //Imprime número de proceso en el rango de procesos y el número assignado según la secuencial de procesos.
    
    cout << "Listo para conexiones... Proceso: " << rank << endl;

    /*int clientAddrSize = sizeof(clientAddr);
    if ((client = accept(server, (SOCKADDR*)&clientAddr, &clientAddrSize)) != INVALID_SOCKET)
    {
        cout << "\n*************** Cliente conectado !! *************\n" << endl;
    }
    closesocket(client);
    cout << "Socket cerrado" << endl;*/

    MPI_Finalize();
    return 0;

}
