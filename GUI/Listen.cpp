#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <ctime>

#include "Listen.h"
#include "CommunicatorSocket.h"


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

bool Listen::listenOnSocket(SOCKET socketName) // method listening for connections
{
    listen(socketName, SOMAXCONN);
    if (listen(socketName, 10) == SOCKET_ERROR) // check for errors
    {
        cout << "Error listening on socket." << endl;
        return true;
    }
    else
        cout << "Listen() is OK." <<endl;
    return true;
}

bool Listen::acceptConnection(SOCKET &socketName, SOCKET &acceptSocketName) // method accepting the connection
{
    servlen = sizeof(service);
    cout << "Waiting for user to connect..." << endl;

    acceptSocketName = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(acceptSocketName = accept(socketName, (SOCKADDR*)&service, &servlen))
    {
        cout << "A coonnection was found" <<endl<<endl;
    }
    socketName = acceptSocketName;
    return true;
}
