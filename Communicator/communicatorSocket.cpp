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
    std::cout << ltm->tm_mday << "." << ltm->tm_mon << "." << 1900 + ltm->tm_year << "," << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec <<endl;
}

DWORD WINAPI CommunicatorSocket::ReadingThread(LPVOID param)
{
    SOCKET s = (SOCKET) param;
    char Buffer[512];
    int iResult;

    do
    {
        std::string message;
        iResult = recv(s, Buffer, 512, 0);
        if (iResult <= 0) break;
        Buffer[iResult] = '\0';
        message = Buffer;
        currentDate();
        std::cout << "Message: " << Buffer << std::endl;
    }
    while (true);

    return 0;
}

// a function for sending and receiving messages for the user who was listening for the connection (type 1)
bool CommunicatorSocket::SendAndReceiveByListeningUser(SOCKET socketName, SOCKET acceptSocketName)
{
    DWORD dwThreadID;
    HANDLE hThread = CreateThread(NULL,0,&ReadingThread,(void*)acceptSocketName,0,&dwThreadID);
    //check for errors
    if (!hThread)
    {
        std::cout << "Error at CreateThread(): " << GetLastError() << std::endl;
        closesocket(acceptSocketName);
        closesocket(socketName);
        WSACleanup();
        return 0;
    }

    //SEND MESSAGES
    do
    {
        std::string message;
        if (!std::getline(std::cin, message))
            break;

        if (send(socketName, message.c_str(), message.length(), 0) == SOCKET_ERROR)
        {
            std::cout << "Error at send(): " << WSAGetLastError() << std::endl;
            break;
        }
    }
    while (true);

    closesocket(acceptSocketName);

    WaitForSingleObject(hThread, INFINITE);
    CloseHandle(hThread);

    closesocket(socketName);
    WSACleanup();
}

// a function for sending and receiving messages for the user who was connecting to listening user (type 2)
bool CommunicatorSocket::SendAndReceiveByConnectingUser(SOCKET socketName)
{
    DWORD dwThreadID;
    HANDLE hThread = CreateThread(NULL, 0, &ReadingThread, (void*)socketName, 0, &dwThreadID);
        if (!hThread)
        {
            std::cout << "Error at CreateThread(): " << GetLastError() << std::endl;
            closesocket(socketName);
            WSACleanup();
            return 0;
        }

        // send messages
        do
        {
            std::string message;
            if (!std::getline(std::cin, message))
                break;

            if (send(socketName, message.c_str(), message.length(), 0) == SOCKET_ERROR)
            {
                std::cout << "Error at send(): " << WSAGetLastError() << std::endl;
                break;
            }
        }
        while (true);

        closesocket(socketName);

        WaitForSingleObject(hThread, INFINITE);
        CloseHandle(hThread);

        WSACleanup();
}
