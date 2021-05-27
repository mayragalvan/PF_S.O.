// Cliente.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

/////////////////////////////////////////////////////////////////////////////////////////////////

/*----------------------------------- PROGRAMA CLIENTE ---------------------------------------*/

/////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <winsock2.h> //Librería para conexión de sockets.
#include <mpi.h> // Librería para MPI.


#pragma warning(disable : 4996) // Comando que desactiva la advertencia del archivo como una amenaza.

using namespace std;

class Client 
{
public:
    WSADATA WSAData; // Estructura que contiene la implementación de Windows Sockets.
    SOCKET server;  // Variable tipo de socket para la conexión para el cliente.
    SOCKADDR_IN addr; // Estructura de recepción de myIP.
    char buffer[1024];
    Client() // Constructor
    {
        WSAStartup(MAKEWORD(2, 0), &WSAData); //Inicialización de la libreria WS2_32.lib.
        server = socket(AF_INET, SOCK_STREAM, 0); //La llamada del scream socket con el protocolo TCP provee el entendimiento entre comunicación.
        addr.sin_addr.s_addr = inet_addr("192.168.1.4"); //ID del server a conectar.
        addr.sin_family = AF_INET; //La familia de TCP/IP Server.
        addr.sin_port = htons(5555); //Port efímero.

        connect(server, (SOCKADDR*)&addr, sizeof(addr)); //Cliente se conectar exitosamente al servidor.
        cout << "\n\t***************** Conectando al Servidor ********************\t\n" << endl;
    }
    //Función que se encarga de enviar los datos en un paquete de bytes, el cliente es quien inicia la comunicación con el servidor.
    void Enviar(int size, int rank)
    {
        cout << "\nEscribir mensaje:" << endl; // Se escribe el mensaje.
        cin >> this->buffer; //Se guarda el mensaje ne el buffer.
        
       ///////////////////////////////////// ENVIO DE PASO DE MENSAJES CON BLOQUE0 DE MPI ////////////////////////////////////
        if (rank == 0)
        {
            for (int s = 1; s < size; ++s)
            {
                MPI_Send(&server, 1, MPI_DOUBLE, s, 173, MPI_COMM_WORLD); //Envia datos del tamaño, tipo, proceso e identificador del mensaje a los procesos hijos.
                cout << " Envio de master: " << this->buffer << "  a esclavo: " << s << endl;
            }
        }
        ///////////////////////////////////// ENVIO DE PASO DE MENSAJES CON BLOQUE0 DE MPI ////////////////////////////////////
        
        send(server, buffer, sizeof(buffer), 0); //Enviar mensaje en el buffer la función es similar a un write())
        cout << "\t------------------- Mensaje enviado! -------------------\t" << endl;
        memset(buffer, 0, sizeof(buffer)); //Se resetea el buffer.

    }// Se envia el paquete de mensaje de escritura.

    //Función que se encarga de recibir y almacenar temporalmente en un size de buffer el mensaje que se recibirá por el cliente.
    void Recibir()
    {
        recv(server, buffer, sizeof(buffer), 0);  //Recibe mensaje del buffer la función es similiar a un read().
        cout << "\nServidor dice: " << buffer << endl;
        memset(buffer, 0, sizeof(buffer));
    }// Se recibió el paquete se hace una lectura del contenido y se libera el buffer.

    //Función encargada de cerrar socket.
    void Cerrar()
    {
        closesocket(server); //Cerrar socket, es decir se cierra la comunicación cuando se desconecta el servidor.
        WSACleanup();
        cout << "***************** Socket cerrado *****************" << endl << endl;
    } //Comunicación terminada.
};

//Función main () contiene el número de argumentos de la línea de comandos.
int main(int argc, char** argv) // números de argumentos y vector de argumentos.
{
    int size; // Número total de procesos.
    int rank; // El rank assignado al proceso de comunicación.
    char name[80]; // Maquina donde corren los procesos.
    int length; // Variable para longitud de la palabra del modelo de maquina.

    /*Inicialización de la ejecución de MPI y su ambiente*/
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // (MPI_COMM_WORLD) es la comunicación por Default de MPI :: Número de rango del proceso actual.
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Número de procesos ejecutados en el grupo default.
    MPI_Get_processor_name(name, &length); // Nombre del dispositivo conectado.

    cout << "\nPROCESOS EN CURSO: " << rank << " size " << size << " on machine: " << name << endl; //Impresión de cada una de los procesos en paralelo.
   
    Client* Cliente = new Client();
    while (true)
    {
        Cliente->Enviar(size,rank); 
        Cliente->Recibir(); // Llama de función Recibir(): El servidor será el primero el recibir el mensaje.
    }
    MPI_Finalize(); /*Termina conexión MPI, bloquea ejecución hasta que terminen los procesos*/
    return 0;
    
}