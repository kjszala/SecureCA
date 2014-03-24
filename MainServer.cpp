#include "Server.h"
using namespace std;

char* Server::getPortNumber(){
	return this->portNumber;
}

void Server::setPortNumber(char *portNumber){
	this->portNumber = portNumber;
}

WSADATA Server::getWsaData(){
	return this->wsaData;
}

void Server::setWsaData(WSADATA wsaData){
	this->wsaData = wsaData;
}

SOCKET Server::getListenSocket(){
	return this->ListenSocket;
}
void Server::setListenSocket(SOCKET socket){
	this->ListenSocket = socket;
}

SOCKET Server::getClientSocket(){
	return this->ClientSocket;
}
void Server::setClientSocket(SOCKET socket){
	this->ClientSocket = socket;
}
