#pragma once

#define KEYPAIR_H_
#define SIZE_KEY 1024

#include <rsa.h>
#include <sha.h>
#include <filters.h>
#include <files.h>
#include <osrng.h>
#include <SecBlock.h>
#include <cryptlib.h>

#include <string>
using std::string;

#include <exception>
using std::exception;

using CryptoPP::RSA;

class KeyPair
{
public:
	KeyPair();
	KeyPair(const KeyPair&);
	KeyPair(const RSA::PublicKey&, const RSA::PrivateKey&);

	~KeyPair() {};

	void setPrivateKey(const RSA::PrivateKey&);
	void setPublicKey(const RSA::PublicKey&);
	RSA::PublicKey getPublicKey() const;
	RSA::PrivateKey getPrivateKey() const;

	string encrypt(string);
	string decrypt(string);

	static void savePrivateKey(const string&, const RSA::PrivateKey&);
	static void savePublicKey(const string&, const RSA::PublicKey&);
	static bool loadPrivateKey(const string&, RSA::PrivateKey&);
	static bool loadPublicKey(const string&, RSA::PublicKey&);

private:
	static void Save(const string&, const CryptoPP::BufferedTransformation&);
	static void Load(const string&, CryptoPP::BufferedTransformation&);

	RSA::PrivateKey privateKey;
	RSA::PublicKey publicKey;
};

