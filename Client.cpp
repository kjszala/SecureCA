#include "Client.h"
using namespace std;

Client::Client(){
	SOCKET ConnectSocket = INVALID_SOCKET;
    struct addrinfo *result = NULL;
    struct addrinfo *ptr = NULL;
	portNumber = (char *)malloc(6);
	ipAddress = (char *)malloc(15);
}

int Client::initialization(){
	// Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &this->getWsaData());
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory( &hints, sizeof(hints) );
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
	iResult = getaddrinfo(this->getIPAddress(), this->getPortNumber(), &hints, &result);
    if ( iResult != 0 ) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Attempt to connect to an address until one succeeds
    for(ptr=result; ptr != NULL ;ptr=ptr->ai_next) {

        // Create a SOCKET for connecting to server
		this->setConnectSocket(socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol));
		if (this->getConnectSocket() == INVALID_SOCKET) {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            return 1;
        }

        // Connect to server.
        iResult = connect( this->getConnectSocket(), ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(this->getConnectSocket());
			this->setConnectSocket(INVALID_SOCKET);
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if (this->getConnectSocket() == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        WSACleanup();
        return 1;
    }
	return 0;
}

int Client::close(){
	// shutdown the connection since no more data will be sent
    iResult = shutdown(this->getConnectSocket(), SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(this->getConnectSocket());
        WSACleanup();
        return 1;
    }

    // cleanup
    closesocket(this->getConnectSocket());
    WSACleanup();
	return 0;
}
