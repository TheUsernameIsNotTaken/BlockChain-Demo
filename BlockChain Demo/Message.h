#pragma once
#include <string>
#include <rsa.h>
#include "SHA_256.h"
#include "KeyPair.h"

using std::string;

class Message
{
public:
	Message() : message(), publicKey(), messageSize(), signature() {};
	Message(string, const KeyPair&);
	~Message() {};

	bool verifier() const;

	bool operator==(const Message& rhs) const
	{
		return (rhs.message == this->message && signature == rhs.signature);
	}
	// For the MultiMap
	Message& operator=(const Message& rhs)
	{
		if (*this == rhs)
			return *this;
		message = rhs.message;
		signature = rhs.signature;
		publicKey = rhs.publicKey;
		messageSize = rhs.messageSize;
		return *this;
	}

	string			getMessage() const;
	RSA::PublicKey  getPublicKey() const;

	SecByteBlock sign(RSA::PrivateKey);
private:
	string			message;
	RSA::PublicKey	publicKey;
	__int64			messageSize;
	SecByteBlock	signature;
};

