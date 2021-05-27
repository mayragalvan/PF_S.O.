
/////////////////////////////////////////////////////////////////////////////////////////////////

/*----------------------------------- PROGRAMA SERVIDOR ---------------------------------------*/

/////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <winsock2.h> //Librería para conexión de sockets.
#include <mpi.h> // Librería para MPI.

using namespace std;

class Server 
{
public:
    WSADATA WSAData; //Se crea el objeto de la estructura WSADATA que contiene la información de la implementación de sockets en Windows, 
    //se asegura que el sistema soporte Winsock2.
    SOCKET server, client; //Variables tipo de socket para la conexión.
    SOCKADDR_IN serverAddr, clientAddr; //Sockets entrantes.
 
    char buffer[1024]; //Espacio de buffer de 1MB
    Server() //Constructor
    {
        WSAStartup(MAKEWORD(2, 0), &WSAData);  //Inicialización de la libreria WS2_32.lib.
        server = socket(AF_INET, SOCK_STREAM, 0); //El stream socket con el protocolo TCP para el entendimiento de la comunicación.
        serverAddr.sin_addr.s_addr = INADDR_ANY; // No genera una IP random.
        serverAddr.sin_family = AF_INET; //La familia de TCP/IP Server.
        serverAddr.sin_port = htons(5555); // El puerto efímero de la comunicacion es 5555.
        bind(server, (SOCKADDR*)&serverAddr, sizeof(serverAddr));  //La función bind es una estructura address que vincula el socket a todas las interfaces disponibles.
        listen(server, 0); //Especifíca el número de mensajes de cliente pendientes, que se ponen el cola para el socket de servidor.

        cout << "\n\t*********************** Server listo para conexiones entrantes. (Ready Listener)... *************************\t\n" << endl;

        int clientAddrSize = sizeof(clientAddr); // El tamaño del address que necesita el cliente es apartado por el S.O. para ser usados por el programa solamente
        if ((client = accept(server, (SOCKADDR*)&clientAddr, &clientAddrSize)) != INVALID_SOCKET) //Cliente es aceptado y se conecta con el socket del address correcto.
        {
            cout << "\n*************** Cliente conectado !! *************\n" << endl;
            cout << "\n\t*************************** Bienvenido al Chat *************************\t\n" << endl;
        }
    }

    //Función que se encarga de recibir y almacenar temporalmente en un size de buffer el mensaje que se recibirá por el cliente.
    void Recibir() 
    {
        recv(client, buffer, sizeof(buffer), 0); //La funcion recv() devuelve el número de bytes leídos y recibidos al buffer apuntado.
        // quien será el que contenga los datos recibidos
        // Si no existe error se retorna un 0 en caso contrario sera un -1.
        cout << "\nCliente dice: " << buffer << endl;
        memset(buffer, 0, sizeof(buffer));

    } // Se recibió el paquete se hace una lectura del contenido y se libera el buffer.

    //Función que se encarga de enviar los datos en un paquete de bytes a partir de los datos de lectura recibidos.
    void Enviar()
    {
        cout << "\nResponder mensaje:" << endl;
        cin >> this->buffer;
        send(client, buffer, sizeof(buffer), 0); // Envia la información en bytes en un paquete donde se trasfieren los datos en este caso, la cadena de mensaje
        memset(buffer, 0, sizeof(buffer));// Resetea la variable del buffer para volver a escribir.
        cout << "\t-----------------Mensaje enviado!-------------------\t" << endl;
    }// Se envia el mensaje de escritura.

    //Función encargada de cerrar socket.
    void CerrarSocket()
    {
        closesocket(client); //Cerrar socket, es decir se cierra la comunicación cuando se desconecta el cliente.
        cout << "Socket cerrado, cliente desconectado." << endl;
    } //Comunicación terminada.
};

//Función main () contiene el número de argumentos de la línea de comandos.
int main(int argc, char** argv) // Números de argumentos y vector de argumentos.
{
    Server* Servidor = new Server(); // Inicialización del objetos de Servidor.
    
    while (true)
    {
        Servidor->Recibir(); // Llama de función Recibir(): El servidor será el primero el recibir el mensaje.
        Servidor->Enviar(); // Lamma de función Enviar(): El servidor envia un mensaje respondiendo.
    }
    MPI_Finalize();
    return 0;
}