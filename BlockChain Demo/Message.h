#pragma once
#include <string>
#include <rsa.h>
#include "SHA_256.h"
#include "KeyPair.h"

using std::string;

class Message
{
public:
	Message(string, KeyPair);
	~Message() {};

	bool verifier() const;

	string			getMessage() const;
	RSA::PublicKey  getPublicKey() const;

	SecByteBlock sign(RSA::PrivateKey&);
private:
	string			message;
	RSA::PublicKey	publicKey;
	__int64			messageSize;
	SecByteBlock	signature;
};

