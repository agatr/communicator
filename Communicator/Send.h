#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <ctime>

using namespace std;

class Send // class for sending
{
public:
    long iResult;
    SOCKADDR_IN conService;
    SOCKET sockSocket;
    SOCKET acceptSocket;
    bool connectToSocket(const char *IP);
    bool initializeWinsockAndCreateSocket();
    bool sendMessage();
    void currentDate();
};
