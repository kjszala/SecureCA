#include "CipherDec.h"

using namespace std;

Ciphering::Ciphering(bool isServer){
	this->setIsServer(isServer);

	if(this->getIsServer()){
		this->thisRSAKey = RSA_new();
		this->otherAESKey = (unsigned char*)malloc(AES_KEYLENGTH/8);

		if(this->readThisRSAKeyFromFile()){
			this->thisRSAKey = this->generateRSAKey();
			this->writeThisRSAKeyToFile();
		}

	}

	else{
		this->otherRSAKey = RSA_new();
		this->readOtherRSAKeyFromFile();
		this->thisAESKey = (unsigned char*)malloc(AES_KEYLENGTH/8);
		this->generateAESKey();
	}
}

Ciphering::~Ciphering(){
	RSA_free(this->getThisRSAKey());
	RSA_free(this->getOtherRSAKey());
	free(this->getThisAESKey());
	free(this->getOtherRSAKey());
}
