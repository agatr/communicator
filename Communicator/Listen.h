#include <conio.h>
#include <stdio.h>
#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#include <ctime>


using namespace std;

class Listen // class for part of the project which listens
{
public:
    SOCKET sockSocket;
    SOCKET communicatorSocket;
    // listenObj.communicatorSocket.initializeWinsockAndCreateSocket();
    SOCKET acceptSocket;
    SOCKADDR_IN service;
    long iResult;
    int servlen;
    bool initializeWinsockAndCreateSocket();
    bool bindSocket(SOCKET socketName);
    bool listenOnSocket();
    bool acceptConnection();
    bool recvMessage();
    void currentDate();
};
