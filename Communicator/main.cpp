#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <ctime>

#include "Listen.h"
#include "Send.h"
#include "CommunicatorSocket.h"


int main()
{
    string IP;
    SOCKET commSocket;
    int userType;

    CommunicatorSocket communicatorObj;
    communicatorObj.initializeWinsockAndCreateSocket(commSocket);

    // Ask the user if he is receiving or sending the message to differenciate which functionalities of the program should be executed
    cout << "Hi, which type of user are you? 1 - Receiver, 2 - Sender" <<endl;
    cin >> userType;

    // depending on the declared user type, execute the methods responsible for listening part
    if (userType == 1)
    {
        Listen listenObj; // I create an object of class Listen
        listenObj.bindSocket(commSocket); // I call the method to bind the socket
        listenObj.listenOnSocket(commSocket); // I call the method to listen for the incoming connection
        listenObj.acceptConnection(commSocket); // accept the connection if any
        listenObj.recvMessage(commSocket); // receive the message if any
    }
    // execute the methods responsible for sending part
    else if (userType == 2)
    {
        Send sendObj; // create an object of class Send
        cout << "Hi what's the IP that you want to connect to?" <<endl;
        cin >> IP;
        sendObj.connectToSocket(IP.c_str(), commSocket); // connect the user to the inputed IP address
        sendObj.sendMessage(commSocket); // call the function responsible for sending messages
    }
    WSACleanup();
    return 0;
}
