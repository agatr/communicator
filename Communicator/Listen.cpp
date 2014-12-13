#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <ctime>

#include "Listen.h"

void Listen::currentDate()
{
    time_t now =  time(0); //current system time
    tm* ltm = localtime(&now); // convert time_t (my now variable) to tm structure as localtime (I have a new var called ltm)
    cout << ltm->tm_mday << "." << ltm->tm_mon << "." << 1900 + ltm->tm_year << "," << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec <<endl;
}

// method responsible for initializing the Winsock
void Listen::initializeWinsock()
{
    WSAData wsaData; // initialize
    iResult = WSAStartup(MAKEWORD(2,1), &wsaData);

    if (iResult != NO_ERROR) // check for errors
         cout << "Error at WSAStartup()" <<endl;
    else
         cout << "WSAStartup() is OK." <<endl;
}

// method creating socket
int Listen::createSocket()
{
    sockSocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP); // create a socket
    if (sockSocket == INVALID_SOCKET) // check for errors
    {
        cout << "Error at socket(): " << WSAGetLastError();
        WSACleanup();
        return 0;
    }
    else
        cout << "Socket() is OK." <<endl;
    return 0;
}

int Listen::bindSocket() // binding the socket to local IP address and port
{
    service.sin_addr.s_addr = inet_addr("0.0.0.0");
    service.sin_family = AF_INET;
    service.sin_port = htons(55555);

    if (bind(sockSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) // cheking for errors
    {
        cout << "Bind() failed." << endl;
        closesocket(sockSocket);
        return 0;
    }
    else
        cout << "Bind() is OK." <<endl;
    return 0;
}

int Listen::listenOnSocket() // method listening for connections
{
    listen(sockSocket, SOMAXCONN);
    if (listen(sockSocket, 10) == SOCKET_ERROR) // check for errors
    {
        cout << "Error listening on socket." << endl;
        return 1;
    }
    else
        cout << "Listen() is OK." <<endl;
    return 0;
}

int Listen::acceptConnection() // method accepting the connection
{
    servlen = sizeof(service);
    cout << "Waiting for user to connect..." << endl;

    acceptSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(acceptSocket = accept(sockSocket, (SOCKADDR*)&service, &servlen))
    {
        cout << "A coonnection was found" <<endl<<endl;
    }
    sockSocket = acceptSocket;
    return 0;
}

int Listen::recvMessage()
{
    do
    {
        std::string message;
        char Buffer[512];
        iResult = recv(sockSocket, Buffer, 512, 0);
        Buffer[iResult] = '\0';
        message = Buffer;
        currentDate();
        std::cout << Buffer <<endl<<endl;

    }while(iResult>0);

    closesocket(sockSocket);
    WSACleanup();
    return 0;
}
