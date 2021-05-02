// Microsoft Development Environment 2003 - Version 7.1.3088

// Copyright (r) 1987-2002 Microsoft Corporation. All Right Reserved

// Microsoft .NET Framework 1.1 - Version 1.1.4322

// Copyright (r) 1998-2002 Microsoft Corporation. All Right Reserved

//

// Run on Windows XP Pro machine, version 2002, SP 2

//

// <windows.h> already included...

// WINVER = 0x0501 for Xp already defined in windows.h



#include <stdio.h>
#include <winsock2.h>


int main()

{

    WORD wVersionRequested;
    WSADATA wsaData;
    int wsaerr;

    // Using MAKEWORD macro, Winsock version request 2.2

    wVersionRequested = MAKEWORD(2, 2);


    wsaerr = WSAStartup(wVersionRequested, &wsaData);
    if (wsaerr != 0)
    {
        /* Tell the user that we could not find a usable */

        /* WinSock DLL.*/

        printf("The Winsock dll not found!\n");

        return 0;
    }
    else
    {

        printf("The Winsock dll found!\n");
        printf("The status: %s.\n", wsaData.szSystemStatus);

    }



    /* Confirm that the WinSock DLL supports 2.2.*/

    /* Note that if the DLL supports versions greater    */

    /* than 2.2 in addition to 2.2, it will still return */

    /* 2.2 in wVersion since that is the version we      */

    /* requested.                                        */

    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
    {
        /* Tell the user that we could not find a usable */

        /* WinSock DLL.*/

        printf("The dll do not support the Winsock version %u.%u!\n", LOBYTE(wsaData.wVersion), HIBYTE(wsaData.wVersion));

        WSACleanup();

        return 0;
    }
    else
    {
        printf("The dll supports the Winsock version %u.%u!\n", LOBYTE(wsaData.wVersion), HIBYTE(wsaData.wVersion));
        printf("The highest version this dll can support: %u.%u\n", LOBYTE(wsaData.wHighVersion), HIBYTE(wsaData.wHighVersion));

    }

    /* The next task... */



    return 0;

}