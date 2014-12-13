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
    int connectToSocket(const char *IP);
    void initializeWinsock();
    int createSocket();
    int sendMessage();
    void currentDate();
};
