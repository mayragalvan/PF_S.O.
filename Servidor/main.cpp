#include <iostream>
#include <winsock2.h>

class Server
{
public:

    WSADATA WSAData;
    SOCKET server, client;
    SOCKADDR_IN serverAddr, clientAddr;
    char buffer[1024];

    Server()
    {
        WSAStartup(MAKEWORD(2, 0), &WSAData);
        server = socket(AF_INET, SOCK_STREAM, 0);
        serverAddr.sin_addr.s_addr = INADDR_ANY;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(5555);
        bind(server, (SOCKADDR *)&serverAddr, sizeof(serverAddr));
        listen(server, 0);
        std::cout << "Listening Input Connections" << std::endl;
        int clientAddSize = sizeof(clientAddr);
        if ((client = accept(server, (SOCKADDR*)&clientAddr, &clientAddSize)) != INVALID_SOCKET)
        {
            std::cout << "Client commercial.." << std::endl;
        }
    }
        void Recibir()
        {
            recv(client, buffer, sizeof(clientAddr), 0);
            std::cout << "Client says" << buffer << std::endl;
            memset(buffer, 0, sizeof(buffer));
        }

        void Enviar()
        {
            std::cout << "Escribe el mensaje a enviar: ";
            std::cin >> this->buffer;
            send(server, buffer, sizeof(buffer), 0);
            memset(buffer, 0, sizeof(buffer));
        }
        void CerrarSocket()
        {
            closesocket(client);
            std::cout << "Client desconected.." << std::endl;
        }
};



int main()
{
    Server* Servidor = new Server();
    while (true)
    {
        Servidor->Recibir();
        Servidor->Enviar();
    }
}
