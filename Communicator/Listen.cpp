#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <ctime>

#include "Listen.h"
#include "communicatorSocket.h"

void Listen::currentDate()
{
    time_t now =  time(0); //current system time
    tm* ltm = localtime(&now); // convert time_t (my now variable) to tm structure as localtime (I have a new var called ltm)
    cout << ltm->tm_mday << "." << ltm->tm_mon << "." << 1900 + ltm->tm_year << "," << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec <<endl;
}

// method responsible for initializing the Winsock
bool Listen::initializeWinsockAndCreateSocket()
{
    WSAData wsaData; // initialize
    iResult = WSAStartup(MAKEWORD(2,1), &wsaData);

    if (iResult != NO_ERROR) // check for errors
         cout << "Error at WSAStartup()" <<endl;
    else
         cout << "WSAStartup() is OK." <<endl;

    // create socket
    sockSocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP); // create a socket
    if (sockSocket == INVALID_SOCKET) // check for errors
    {
        cout << "Error at socket(): " << WSAGetLastError();
        WSACleanup();
        return true;
    }
    else
        cout << "Socket() is OK." <<endl;
    return true;
}

bool Listen::bindSocket(SOCKET socketName) // binding the socket to local IP address and port
{
    service.sin_addr.s_addr = inet_addr("0.0.0.0");
    service.sin_family = AF_INET;
    service.sin_port = htons(55555);

    if (bind(socketName, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) // cheking for errors
    {
        cout << "Bind() failed." << endl;
        closesocket(socketName);
        return true;
    }
    else
        cout << "Bind() is OK." <<endl;
    return true;
}

bool Listen::listenOnSocket() // method listening for connections
{
    listen(sockSocket, SOMAXCONN);
    if (listen(sockSocket, 10) == SOCKET_ERROR) // check for errors
    {
        cout << "Error listening on socket." << endl;
        return true;
    }
    else
        cout << "Listen() is OK." <<endl;
    return true;
}

bool Listen::acceptConnection() // method accepting the connection
{
    servlen = sizeof(service);
    cout << "Waiting for user to connect..." << endl;

    acceptSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(acceptSocket = accept(sockSocket, (SOCKADDR*)&service, &servlen))
    {
        cout << "A coonnection was found" <<endl<<endl;
    }
    sockSocket = acceptSocket;
    return true;
}

bool Listen::recvMessage()
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
    //enters indefinite loop and sends last message forever
    /*while((sockSocket != INVALID_SOCKET) || (iResult>0));*/

    closesocket(sockSocket);
    WSACleanup();
    return true;
}
