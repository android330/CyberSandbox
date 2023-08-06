#include <iostream>
#include <winsock.h>
#include <stdio.h>

#define PORT 8787


void main(){
    std::cout << "Hello World" << std::endl;
    SOCKET ListenSocket;

    int new_socket, valread;
    struct sockaddr_in address;
    BOOL opt = FALSE;
    int addrlen = sizeof(address);

    WSADATA wsaData;
    if(WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR){
        perror("Winsock init");
        exit(EXIT_FAILURE);
    }

    // Creating socket file descriptor
    if ((ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == 0){
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully setting socket to the port 8787
    if (setsockopt(ListenSocket, SOL_SOCKET, SO_REUSEADDR , (char*) &opt, sizeof(BOOL)) ==  SOCKET_ERROR){
        std::cout << WSAGetLastError() << std::endl;
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    // Forcefully attaching socket to the port 8787
    if (bind(ListenSocket, (struct sockaddr *)&address,sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    //listens
    if (listen(ListenSocket, 3) < 0){
        perror("listen");
        exit(EXIT_FAILURE);
    }

    //accept connections on correct socket
    if ((new_socket = accept(ListenSocket, (struct sockaddr *)&address,(int*)&addrlen))<0){
        perror("accept");
        exit(EXIT_FAILURE);
    }


    //blocking while loop for recieving data
    char buffer[1024] = {0};
    std::string readString = "";
    while(true){
        memset(&buffer[0], 0, sizeof(buffer));
        valread = recv( new_socket , buffer, 1024, 0);

        if (valread)
        {
            readString = buffer;
            std::cout << readString << std::endl;
        }

        //if connection close transition to server
        else 
        {
            closesocket(new_socket);
            WSACleanup();
        }
    }
    return;
    
}