#include "CipherDec.h"

using namespace std;

RSA* Ciphering::getThisRSAKey(){
	return this->thisRSAKey;
}

RSA* Ciphering::getOtherRSAKey(){
	return this->otherRSAKey;
}

unsigned char* Ciphering::getThisAESKey(){
	return this->thisAESKey;
}

unsigned char* Ciphering::getOtherAESKey(){
	return this->otherAESKey;
}

void Ciphering::setThisAESKey(unsigned char* thisAESKey){
	this->thisAESKey = thisAESKey;
}

void Ciphering::setOtherAESKey(unsigned char* otherAESKey){
	this->otherAESKey = otherAESKey;
}

void Ciphering::setThisRSAKey(RSA* thisRSAKey){
	this->thisRSAKey = thisRSAKey;
}

void Ciphering::setOtherRSAKey(RSA* otherRSAKey){
	this->otherRSAKey = otherRSAKey;
}

void Ciphering::setIsServer(bool isServer){
	this->isServer = isServer;
}

bool Ciphering::getIsServer(){
	return this->isServer;
}
