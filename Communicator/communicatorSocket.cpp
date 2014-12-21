#include <conio.h>
#include <stdio.h>
#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#include <ctime>

#include "communicatorSocket.h"
#include "Listen.h"

using namespace std;

bool CommunicatorSocketClass::initializeWinsockAndCreateSocket()
{
    WSAData wsaData; // initialize
    iResult = WSAStartup(MAKEWORD(2,1), &wsaData);

    if (iResult != NO_ERROR) // check for errors
         cout << "Error at WSAStartup()" <<endl;
    else
         cout << "WSAStartup() is OK." <<endl;

    // create socket
    communicatorSocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP); // create a socket
    if (communicatorSocket == INVALID_SOCKET) // check for errors
    {
        cout << "Error at socket(): " << WSAGetLastError();
        WSACleanup();
        return true;
    }
    else
        cout << "Socket() is OK." <<endl;
    return true;
}
