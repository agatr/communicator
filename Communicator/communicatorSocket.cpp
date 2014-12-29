#include <conio.h>
#include <stdio.h>
#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#include <ctime>

#include "CommunicatorSocket.h"
#include "Listen.h"

using namespace std;

bool CommunicatorSocket::initializeWinsockAndCreateSocket(SOCKET &socketName)
{
    WSAData wsaData; // initialize
    iResult = WSAStartup(MAKEWORD(2,1), &wsaData);

    if (iResult != NO_ERROR) // check for errors
         cout << "Error at WSAStartup()" <<endl;
    else
         cout << "WSAStartup() is OK." <<endl;

    // create socket
    socketName = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP); // create a socket
    if (socketName == INVALID_SOCKET) // check for errors
    {
        cout << "Error at socket(): " << WSAGetLastError();
        WSACleanup();
        return true;
    }
    else
        cout << "Socket() is OK." <<endl;
    return true;
}

void CommunicatorSocket::currentDate()
{
    time_t now =  time(0); //current system time
    tm* ltm = localtime(&now); // convert time_t (my now variable) to tm structure as localtime (I have a new var called ltm)
    cout << ltm->tm_mday << "." << ltm->tm_mon << "." << 1900 + ltm->tm_year << "," << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec <<endl;
}
