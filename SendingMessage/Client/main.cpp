//CLIENT

#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <ctime>

using namespace std;

int main()
{
    /* ======= date and time ===== */
    time_t now =  time(0); //current system time
    tm* ltm = localtime(&now); // convert time_t (my now variable) to tm structure as localtime (I have a new var called ltm)
    /* ========= date and time end ========== */

    string confirm;
    char message[200];
    char sName[200];

    WSAData wsaData;
    long iResult = WSAStartup(MAKEWORD(2,1), &wsaData);

    if (iResult != NO_ERROR)
         cout << "Client: Error at WSAStartup()" <<endl;
    else
         cout << "Client: WSAStartup() is OK." <<endl;


    SOCKADDR_IN clientService;
    int addrlen = sizeof(clientService);


    SOCKET m_socket;
    m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (m_socket == INVALID_SOCKET)
    {
        cout << "Client: socket() - Error at socket(): " << WSAGetLastError();
        WSACleanup();
        return 0;
    }
    else
       cout << "Client: socket() is OK." <<endl;


    clientService.sin_addr.s_addr = inet_addr("192.168.1.101");
    clientService.sin_family = AF_INET;
    clientService.sin_port = htons(55555);


    cout << "Do you want to connect to the server? [Y/N]" <<endl;
    cin >> confirm;
    cout <<endl;

    if(confirm == "N")
    {
        exit(1);
    }
    else
    {
        if(confirm == "Y")
        {
            if (connect(m_socket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR)
            {
                cout << "Client: connect() - Failed to connect: " << WSAGetLastError();
                WSACleanup();
                return 0;
            }
            else
            {
                // receive the "name" of the server - in server i firstly ask to input the name so that the client knows the name
                iResult = recv(m_socket, sName, sizeof(message), 0);

                for (;;)
                {

                    iResult = recv(m_socket, message, sizeof(message), 0);
                    // strmessage = message;
                    // this will have to be the time when sender sent message -> ??
                    cout << ltm->tm_mday << "." << ltm->tm_mon << "." << 1900 + ltm->tm_year << "," << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec <<endl;
                    // I show who (sName - "name of the server") and what (message) wrote
                    cout << sName << ": " << message <<endl <<endl;

                    getchar();
                }
            }
        }
    }
    getchar();
}
