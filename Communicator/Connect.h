#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <ctime>

using namespace std;

class Connect // class for sending
{
public:
    long iResult;
    SOCKADDR_IN conService;
    SOCKET acceptSocket;
    bool connectToSocket(const char *IP, SOCKET &socketName);
};
