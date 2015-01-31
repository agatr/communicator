#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <ctime>
#include <tchar.h>
#include <windows.h>

#include "Listen.h"
#include "Connect.h"
#include "CommunicatorSocket.h"


/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");
HWND TextBox, SendButton, TextField, RadioButton[2], IPTextBox, ConnectButton, ListenButton, UsersList;
long iResult;
SOCKET commSocket;
SOCKET acceptSocket;
CommunicatorSocket communicatorObj;
Connect connectObj;
Listen listenObj;

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND+7;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("Communicator"),  /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           660,                 /* The programs width */
           370,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Socket initialization */
    communicatorObj.initializeWinsockAndCreateSocket(commSocket);

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}

/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
        case WM_CREATE:

            //=====BOXES=====//
            TextBox = CreateWindow("EDIT",
                                   "",
                                   WS_BORDER | WS_CHILD | WS_VISIBLE,
                                   10, 300, 390, 20,
                                   hwnd, NULL, NULL, NULL);

            TextField = CreateWindow("EDIT",
                                     "",
                                     WS_VISIBLE | WS_CHILD | WS_BORDER | ES_READONLY,
                                     10, 90, 465, 200,
                                     hwnd, NULL, NULL, NULL);

            // Radiobuttons are not yet working, I made separate buttons for connecting and listening. Then, I'll make one button and depending on what the user chooses, I'll either execute connect or listen functions
            RadioButton[0] = CreateWindow("BUTTON",
                                       "waiting",
                                       WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                                       10, 10, 100, 20,
                                       hwnd, NULL, NULL, NULL);

            RadioButton[1] = CreateWindow("BUTTON",
                                       "connecting to:",
                                       WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                                       10, 40, 120, 20,
                                       hwnd, NULL, NULL, NULL);

            IPTextBox= CreateWindow("EDIT",
                                   "",
                                   WS_BORDER | WS_CHILD | WS_VISIBLE,
                                   130, 40, 200, 20,
                                   hwnd, NULL, NULL, NULL);

            UsersList = CreateWindow("STATIC",
                                   "",
                                   WS_BORDER | WS_CHILD | WS_VISIBLE,
                                   485, 10, 150, 310,
                                   hwnd, NULL, NULL, NULL);

            //=====BUTTONS=====//
            ListenButton = CreateWindow("BUTTON",
                         "Listen",
                         WS_VISIBLE | WS_CHILD,
                         410, 10, 65, 20,
                         hwnd, (HMENU) 1, NULL, NULL);

            ConnectButton = CreateWindow("BUTTON",
                         "Connect",
                         WS_VISIBLE | WS_CHILD,
                         410, 40, 65, 20,
                         hwnd, (HMENU) 2, NULL, NULL);

            SendButton = CreateWindow("BUTTON",
                         "Send",
                         WS_VISIBLE | WS_CHILD,
                         410, 300, 65, 20,
                         hwnd, (HMENU) 3, NULL, NULL);
            break;

        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case 1:
                    {
                        // I check if the socket is initialized
                        if ((communicatorObj.initializeWinsockAndCreateSocket(commSocket)) == TRUE)
                        {
                            listenObj.bindSocket(commSocket);
                            listenObj.listenOnSocket(commSocket);
                            listenObj.acceptConnection(commSocket, acceptSocket); // accept the connection if any
                            //communicatorObj.SendAndReceiveByListeningUser(commSocket, acceptSocket);*/
                        }
                        else
                            cout << "Something went wrong, please restart the program.";
                    }
                break;

                case 2:
                    {
                        string IP = "192.168.1.101";

                        if ((communicatorObj.initializeWinsockAndCreateSocket(commSocket)) == TRUE)
                        {
                            connectObj.connectToSocket(IP.c_str(), acceptSocket); // connect the user to the inputed IP address
                            //communicatorObj.SendAndReceiveByConnectingUser(acceptSocket);
                        }
                        else
                            cout << "Something went wrong, please restart the program.";
                    }
                break;

                case 3:
                    {
                        //get the text from TextBox
                        int len = GetWindowTextLength(TextBox) + 1;
                        char* text = new char[len];
                        GetWindowText(TextBox, &text[0], len);

                        //append the text to TextField
                        SendMessage(TextField, EM_SETSEL, -1, -1);
                        SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)&text[0]);
                        delete[] text;
                        //Delete the text from TextBox
                        SetWindowText(TextBox, "");
                    }
                break;
            }
        break;

        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
