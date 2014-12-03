//SERVER
#include <conio.h>
#include <stdio.h>
#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#include <ctime>


using namespace std;

int main()
{
    /* ======= date and time ===== */
    time_t now =  time(0); //current system time
    tm* ltm = localtime(&now); // convert time_t (my now variable) to tm structure as localtime (I have a new var called ltm)
    /* ========= date and time end ========== */


    WSAData wsaData;
    long iResult = WSAStartup(MAKEWORD(2,1), &wsaData);
    if (iResult != NO_ERROR)
    cout << "Server: Error at WSAStartup()"  <<endl;
        else
    cout << "Server: WSAStartup() is OK." <<endl;


    SOCKADDR_IN service;
    int servlen = sizeof(service);
    service.sin_addr.s_addr = inet_addr("0.0.0.0");
    service.sin_family = AF_INET;
    service.sin_port = htons(55555);


    SOCKET ListenSocket;
    ListenSocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if (ListenSocket == INVALID_SOCKET)
        {
            cout << "Server: Error at socket(): " << WSAGetLastError();
            WSACleanup();
            return 0;
        }
        else
            cout << "Server: socket() is OK." <<endl;


    if (bind(ListenSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR)
    {
        cout << "Server: bind() failed." << endl;
        closesocket(ListenSocket);
        return 0;
    }
    else
        cout << "Server: bind() is OK." <<endl;


    listen(ListenSocket, SOMAXCONN);
    if (listen(ListenSocket, 10) == SOCKET_ERROR)
        cout << "Server: Error listening on socket." << endl;
    else
        cout << "Server: listen() is OK." <<endl;

    SOCKET AcceptSocket;
    cout << "Server: Waiting for client to connect..." << endl;

    AcceptSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    char message[500];
    char sName[500];

    if(AcceptSocket = accept(ListenSocket, (SOCKADDR*)&service, &servlen))
    {
        cout << "A coonnection was found" <<endl<<endl;
        cout << "Tell the receiver what your name is" <<endl;
        cin >> sName;
        cout <<endl;

        // I had NULL here as last argument, but it gave me warning so i put 0 - is that right?
        iResult = send(AcceptSocket, sName, 12, 0);

        for (;;)
        {
            cout << ltm->tm_mday << "." << ltm->tm_mon << "." << 1900 + ltm->tm_year << "," << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec <<endl;
            cout << sName << ": ";
            cin >> message;
            iResult = send(AcceptSocket, message, 12, 0);
            cout <<endl;
        }
    }

    WSACleanup();
    return 0;
}
