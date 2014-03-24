#include "Server.h"
using namespace std;

Server::Server(){
	SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;
    struct addrinfo *result = NULL;
	portNumber = (char *)malloc(6);
}

int Server::initialization(){
	// Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &this->getWsaData());
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    iResult = getaddrinfo(NULL, portNumber, &hints, &result);
    if ( iResult != 0 ) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Create a SOCKET for connecting to server
	this->setListenSocket(socket(result->ai_family, result->ai_socktype, result->ai_protocol));
    if (ListenSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    // Setup the TCP listening socket
    iResult = bind( this->getListenSocket(), result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(this->getListenSocket());
        WSACleanup();
        return 1;
    }

    freeaddrinfo(result);

    iResult = listen(this->getListenSocket(), SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(this->getListenSocket());
        WSACleanup();
        return 1;
    }

    // Accept a client socket
    this->setClientSocket(accept(this->getListenSocket(), NULL, NULL));
    if (this->getClientSocket() == INVALID_SOCKET) {
        printf("accept failed with error: %d\n", WSAGetLastError());
        closesocket(this->getClientSocket());
        WSACleanup();
        return 1;
    }
	return 0;
}

int Server::close(){
	// shutdown the connection since we're done
    iResult = shutdown(this->getClientSocket(), SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(this->getClientSocket());
        WSACleanup();
        return 1;
    }
	// cleanup
    closesocket(this->getClientSocket());
    WSACleanup();
	return 0;
}
