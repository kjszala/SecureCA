#include <openssl/rand.h>
#include <openssl/rsa.h>
#include <openssl/aes.h>
#include <openssl/pem.h>

#include <stdio.h>
#include <string>
#include <string.h>
#include <iostream>
#include <fstream>

#ifndef CIPHERDEC_H
#define CIPHERDEC_H

#define RSA_KEYLENGTH 4096
#define RSA_E 65537


#define THISPRIVATERSA "C:\\Users\\kszala\\Documents\\Visual Studio 2012\\Projects\\SecureCAServer\\Debug\\privateRSAKey.pem"
#define THISPUBLICRSA "C:\\Users\\kszala\\Documents\\Visual Studio 2012\\Projects\\SecureCAServer\\Debug\\publicRSAKey.pem"

#define OTHERPUBLICRSA "C:\\Users\\kszala\\Documents\\Visual Studio 2012\\Projects\\SecureCAServer\\Debug\\publicRSAKey.pem"

#define AES_KEYLENGTH 256


class Ciphering{

public:
	Ciphering(bool isServer);
	~Ciphering();

	RSA* generateRSAKey();
	void generateAESKey();

	int writeThisRSAKeyToFile();

	int readThisRSAKeyFromFile();
	int readOtherRSAKeyFromFile();

	RSA* getThisRSAKey();
	RSA* getOtherRSAKey();
	
	void setThisRSAKey(RSA* thisRSAKey);
	void setOtherRSAKey(RSA* otherRSAKey);

	unsigned char* getThisAESKey();
	unsigned char* getOtherAESKey();

	void setThisAESKey(unsigned char* thisAESKey);
	void setOtherAESKey(unsigned char* otherAESKey);

	void setIsServer(bool isServer);
	bool getIsServer();

private:
	RSA* thisRSAKey;
	RSA* otherRSAKey;

	unsigned char *thisAESKey;
	unsigned char *otherAESKey;

	bool isServer;
};

#endif
