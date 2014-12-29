#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <ctime>

#include "Send.h"
#include "CommunicatorSocket.h"

bool Send::connectToSocket(const char *IP, SOCKET socketName) // connect to  socket based on the IP given as an argument (in main() I ask the user to give the IP)
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

bool Send::sendMessage(SOCKET socketName) // sending messages in infinite loop
{
    for (;;)
    {
        std::string message;
        std::getline(std::cin, message);
        unsigned int Length = strlen(message.c_str());
        if(Length>512)
            Length = 512;

        time_t now =  time(0); //current system time
        tm* ltm = localtime(&now); // convert time_t (my now variable) to tm structure as localtime (I have a new var called ltm)
        cout << ltm->tm_mday << "." << ltm->tm_mon << "." << 1900 + ltm->tm_year << "," << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec <<endl;


        iResult = send(socketName, message.c_str(),Length,0);
    }
    //closesocket(socketName);
    WSACleanup();
    return true;
}
