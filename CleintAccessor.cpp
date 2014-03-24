#include "Client.h"
using namespace std;

char* Client::getPortNumber(){
	return this->portNumber;
}

void Client::setPortNumber(char *portNumber){
	this->portNumber = portNumber;
}

char* Client::getIPAddress(){
	return this->ipAddress;
}

void Client::setIPAddress(char *ipAddress){
	this->ipAddress = ipAddress;
}


WSADATA Client::getWsaData(){
	return this->wsaData;
}

void Client::setWsaData(WSADATA wsaData){
	this->wsaData = wsaData;
}

SOCKET Client::getConnectSocket(){
	return this->ConnectSocket;
}
void Client::setConnectSocket(SOCKET socket){
	this->ConnectSocket = socket;
}
