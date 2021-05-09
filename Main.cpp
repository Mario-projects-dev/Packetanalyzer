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
    ///////create a socket//////////
    //socket obejct m_socket
    SOCKET m_socket;

    //for function socket use internet family, streaming socket and TCP/IP protocol
    //using AF_INET family, TCP socket type and protocol of the AF_INET - IPv4
    m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    //check that the socket is a valid socket
    
    if (m_socket == INVALID_SOCKET)
    {
        printf("Error at socket: %ld\n", WSAGetLastError());
        WSACleanup();//wsacleanup() - returns 0 if operation was successful
        return 0;
    }
    else
    {
        printf("socket function is working!\n");
    }
    ///////// function bind()/////////
    //create sockaddr_in object and set its values
    sockaddr_in service;

    //AF_INET is the Internet address family
    service.sin_family = AF_INET;

    //127.0.0.1 is the local ip address to which will be socket bound
    service.sin_addr.s_addr = inet_addr("127.0.0.1");

    //55555 is port number to which will be socket bound
    service.sin_port = htons(55555);

    if (bind(m_socket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR)
    {
        printf("bind function failed: %ld.\n", WSAGetLastError());
        closesocket(m_socket);//closesocet function close the socket
        return 0;
    }
    else
    {
        printf("bind is working\n");
    }

    //call listen function, passing created socket and the maximum number of allowed 
    //connections to accept as parameters. check for general errors
    if (listen(m_socket, 1) == SOCKET_ERROR)
        printf("listen function: Error on listening socket %ld.\n", WSAGetLastError());
    else
    {
        printf("listen function working correctly, I am waiting for connections...\n");
    }
    //temporary socket AcceptSocket for accepting connections
    SOCKET AcceptSocket;

    printf("Server: Waiting for a client to connect...\n");
    printf("Server is ready...run your client program...\n");
    //verification loop to checks for connection requests, if connection request occurs, call accept function to handle the request
    while (1)
    {
        AcceptSocket = SOCKET_ERROR;
        while (AcceptSocket == SOCKET_ERROR)
        {
            AcceptSocket = accept(m_socket, NULL, NULL);
        }
        //when connection is accepted, transfer control from temporary socket to original socket and stop checking for new connection
        printf("Server:Client connected!\n");
        m_socket = AcceptSocket;
        break;
    }

    return 0;

}