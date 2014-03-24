#include "CipherDec.h"

using namespace std;

int Ciphering::readThisRSAKeyFromFile(){
	FILE* filePrivateRSAKey;

	filePrivateRSAKey = fopen(THISPRIVATERSA, "r");

	if(filePrivateRSAKey != NULL){
		if(!PEM_read_RSAPrivateKey(filePrivateRSAKey,&this->thisRSAKey,NULL,NULL)){
			fclose(filePrivateRSAKey);
			return 1;
		}
		fclose(filePrivateRSAKey);
		return 0;
	}
	return 1;
}

int Ciphering::readOtherRSAKeyFromFile(){
	FILE* fileOtherPublicRSAKey;

	fileOtherPublicRSAKey = fopen(OTHERPUBLICRSA, "r");

	if(fileOtherPublicRSAKey != NULL){
		if(!PEM_read_RSAPublicKey(fileOtherPublicRSAKey, &this->otherRSAKey, NULL, NULL)){
			fclose(fileOtherPublicRSAKey);
			return 1;
		}
		fclose(fileOtherPublicRSAKey);
		return 0;
	}
	return 1;
}
