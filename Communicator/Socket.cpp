#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <ctime>

#include "Socket.h"

using namespace std;

// method responsible for initializing the Winsock
void Socket::initializeWinsock()
{
    WSAData wsaData; // initialize
    iResult = WSAStartup(MAKEWORD(2,1), &wsaData);

    if (iResult != NO_ERROR) // check for errors
         cout << "Error at WSAStartup()" <<endl;
    else
         cout << "WSAStartup() is OK." <<endl;
}

// method creating socket
int Socket::createSocket()
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

// method responsible for detecting current date and time and displaying it (sort of heading for message)
void Socket::currentDate()
{
    time_t now =  time(0); //current system time
    tm* ltm = localtime(&now); // convert time_t (my now variable) to tm structure as localtime (I have a new var called ltm)
    cout << ltm->tm_mday << "." << ltm->tm_mon << "." << 1900 + ltm->tm_year << "," << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec;
}
