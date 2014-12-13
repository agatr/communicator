#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <ctime>

#include "Send.h"

void Send::currentDate()
{
    time_t now =  time(0); //current system time
    tm* ltm = localtime(&now); // convert time_t (my now variable) to tm structure as localtime (I have a new var called ltm)
    cout << ltm->tm_mday << "." << ltm->tm_mon << "." << 1900 + ltm->tm_year << "," << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec <<endl;
}

// method responsible for initializing the Winsock
void Send::initializeWinsock()
{
    WSAData wsaData; // initialize
    iResult = WSAStartup(MAKEWORD(2,1), &wsaData);

    if (iResult != NO_ERROR) // check for errors
         cout << "Error at WSAStartup()" <<endl;
    else
         cout << "WSAStartup() is OK." <<endl;
}

// method creating socket
int Send::createSocket()
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

int Send::connectToSocket(const char *IP) // connect to  socket based on the IP given as an argument (in main() I ask the user to give the IP)
{
    conService.sin_addr.s_addr = inet_addr(IP); // connect to the ipnuted IP
    conService.sin_family = AF_INET;
    conService.sin_port = htons(55555); // should the port also be the argument?

    if (connect(sockSocket, (SOCKADDR*)&conService, sizeof(conService)) == SOCKET_ERROR) // check for errors
    {
        cout << "Failed to connect: " << WSAGetLastError();
        WSACleanup();
        return 0;
    }
    else
    {
        cout << "Connected." <<endl;
    }
    return 0;
}

int Send::sendMessage() // sending messages in infinite loop
{
    for (;;)
    {
        std::string message;
        std::getline(std::cin, message);
        unsigned int Length = strlen(message.c_str());
        if(Length>512)
            Length = 512;
        currentDate();
        iResult = send(sockSocket, message.c_str(),Length,0);
    }
    closesocket(sockSocket);
    WSACleanup();
    return 0;
}
