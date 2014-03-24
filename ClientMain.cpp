#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <openssl/applink.c>
#include "CipherDec.h"
#include "MessageDivide.h"
#include "Client.h"

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


using namespace std;

int main(void) 
{
	Ciphering *ciphering = new Ciphering(false);
	AES_KEY aes_key;	
	AES_set_encrypt_key(ciphering->getThisAESKey(), 256, &aes_key);
	Client *client = new Client();
	client->setIPAddress("127.0.0.1");
	client->setPortNumber("8080");
	client->initialization();
	
	//sending!!!!!!!!!!!!
	// to initialize sendbuf will store data
	// first message that is sent from client to server is
	// encrypted using otherRSApublic Key thisAESkey
	// then next message is sent encrypted using AESkey to remember every message
	// encrypted using AES can't be longer than 16bytes(128 bites)
	// AESkey is 256 bites long( 32bytes) RSA_size is 512 bites
	unsigned char *msgEncrypredAESKey;

	msgEncrypredAESKey = (unsigned char*)malloc(RSA_KEYLENGTH/8);

	RSA_public_encrypt(AES_KEYLENGTH/8, ciphering->getThisAESKey() , msgEncrypredAESKey, ciphering->getOtherRSAKey(), RSA_PKCS1_PADDING);	
	client->iResult = send( client->getConnectSocket(), (const char*) msgEncrypredAESKey, RSA_KEYLENGTH/8, 0 );
    if (client->iResult == SOCKET_ERROR) {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(client->getConnectSocket());
        WSACleanup();
        return 1;
    }

	free(msgEncrypredAESKey);

	unsigned char *msgEncrypredByAES;
	unsigned char *message;

	msgEncrypredByAES = (unsigned char*)malloc(128/8);
	message = (unsigned char *)malloc(128/8);

	do{
		gets((char *)message);
		//TO DO: receive message from UI in java ciphering and sending when receiving from JAVA
		AES_encrypt(message,msgEncrypredByAES,&aes_key);
		client->iResult = send( client->getConnectSocket(),(const char*)msgEncrypredByAES,128/8, 0 );
		
		if (client->iResult == SOCKET_ERROR) {
			printf("send failed with error: %d\n", WSAGetLastError());
			closesocket(client->getConnectSocket());
			WSACleanup();
			return 1;
		}
	} while (true);
    
	client->close();
    
	system("PAUSE");
    return 0;
}






	//Ciphering *ciphering = new Ciphering();
	//AES_KEY aes_key;
	//Message *message = new Message();


	//PEM_write_RSAPublicKey(stdout, ciphering->getThisRSAKey());
	//PEM_write_RSAPrivateKey(stdout, ciphering->getThisRSAKey(),NULL,NULL,0,NULL,NULL);

	//ciphering->writeThisRSAKeyToFile();
	//ciphering->readOtherRSAKeyFromFile();

	//PEM_write_RSAPublicKey(stdout, ciphering->getOtherRSAKey());


	/*
	//to set encryption via AES
	AES_set_encrypt_key(ciphering->getThisAESKey(), 256, &aes_key);
	AES_encrypt((unsigned char *)message,(unsigned char *)encrypted,&aes_key);


	//to set decryption via AES
	AES_set_decrypt_key(ciphering->getThisAESKey(), 256, &aes_key);
	AES_decrypt((unsigned char *)encrypted,(unsigned char *)decrypted,&aes_key);

	//to set encryption/decryption via RSA
	int i = RSA_public_encrypt(AES_KEYLENGTH/8, ciphering->getThisAESKey() ,(unsigned char *) encrypted, ciphering->getThisRSAKey(), RSA_PKCS1_PADDING);
	RSA_private_decrypt(i,(unsigned char *) encrypted,(unsigned char *) decrypted, ciphering->getThisRSAKey(), RSA_PKCS1_PADDING);
	*/
