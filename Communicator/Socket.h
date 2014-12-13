#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include <stdio.h>

class Socket // class Socket - this class is not dependent on if the object of the class sends or listens - it has methods common for both of them
{
public:
    long iResult;
    SOCKET sockSocket;
    void initializeWinsock();
    int createSocket();
    void currentDate();
};
