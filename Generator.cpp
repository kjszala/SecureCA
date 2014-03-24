#include "CipherDec.h"

using namespace std;

RSA* Ciphering::generateRSAKey(){
	return RSA_generate_key(RSA_KEYLENGTH, RSA_E, NULL, NULL);
}

void Ciphering::generateAESKey(){
	RAND_bytes(this->thisAESKey, AES_KEYLENGTH/8);
}
