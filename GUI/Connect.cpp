#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <ctime>

#include "Connect.h"
#include "CommunicatorSocket.h"

bool Connect::connectToSocket(const char *IP, SOCKET &socketName) // connect to  socket based on the IP given as an argument (in main() I ask the user to give the IP)
{
    conService.sin_addr.s_addr = inet_addr(IP); // connect to the ipnuted IP
    conService.sin_family = AF_INET;
    conService.sin_port = htons(55555); // should the port also be the argument?

    if (connect(socketName, (SOCKADDR*)&conService, sizeof(conService)) == SOCKET_ERROR) // check for errors
    {
        cout << "Failed to connect: " << WSAGetLastError();
        WSACleanup();
        return true;
    }
    else
    {
        cout << "Connected." <<endl;
    }
    return true;
}
