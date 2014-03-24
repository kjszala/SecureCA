#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef SERVER_H
#define SERVER_H

#define RSA_KEYLENGTH 4096
#define RSA_E 65537

class Server{
public:
	Server();
	~Server();

	int initialization();
	int close();

	WSADATA getWsaData();
	void setWsaData(WSADATA wsData);

    SOCKET getListenSocket();
	void setListenSocket(SOCKET socket);

	SOCKET getClientSocket();
	void setClientSocket(SOCKET socket);

	char *getPortNumber();
	void setPortNumber(char* portNumber);

	struct addrinfo *result;
    struct addrinfo hints;

    int iResult;

private:
	WSADATA wsaData;
	SOCKET ListenSocket;
    SOCKET ClientSocket;
	char *portNumber;
};

#endif
