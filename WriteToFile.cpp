#include "CipherDec.h"

using namespace std;

int Ciphering::writeThisRSAKeyToFile(){
	FILE* filePrivateRSAKey;
	FILE* filePublicRSAKey;

	filePrivateRSAKey = fopen(THISPRIVATERSA, "w");
	filePublicRSAKey = fopen(THISPUBLICRSA, "w");

	PEM_write_RSAPrivateKey(filePrivateRSAKey,this->getThisRSAKey(),NULL,NULL,0,NULL,NULL);
	PEM_write_RSAPublicKey(filePublicRSAKey,this->getThisRSAKey());

	fclose(filePrivateRSAKey);
	fclose(filePublicRSAKey);

	return 0;
}
