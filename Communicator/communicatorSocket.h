#include <conio.h>
#include <stdio.h>
#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#include <ctime>

using namespace std;

class CommunicatorSocketClass // class Socket - this class is not dependent on if the object of the class sends or listens - it has methods common for both of them
{
public:
    long iResult;
    SOCKET communicatorSocket;
    bool initializeWinsockAndCreateSocket();
    //bool createSocket();
    void currentDate();
};
