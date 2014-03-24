#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef CLIENT_H
#define CLIENT_H

#define RSA_KEYLENGTH 4096
#define RSA_E 65537


class Client{
public:
	Client();
	~Client();

	int initialization();
	int close();

	WSADATA getWsaData();
	void setWsaData(WSADATA wsData);

	SOCKET getConnectSocket();
	void setConnectSocket(SOCKET socket);

	char *getPortNumber();
	void setPortNumber(char* portNumber);

	char *getIPAddress();
	void setIPAddress(char* ipAddress);
	
    
    struct addrinfo *result;
	struct addrinfo *ptr;
	struct addrinfo hints;
	int iResult;
	
private:
	SOCKET ConnectSocket;
	WSADATA wsaData;
	char *portNumber;
	char *ipAddress;
};

#endif
