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
        SOCKET acceptSocket;
        SOCKADDR_IN service;
        long iResult;
        int servlen;
        bool bindSocket(SOCKET socketName);
        bool listenOnSocket(SOCKET socketName);
        bool acceptConnection(SOCKET socketName);
        bool recvMessage(SOCKET socketName);
};
