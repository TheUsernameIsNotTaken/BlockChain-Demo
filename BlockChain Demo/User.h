#pragma once
#include <string>
#include <vector>
#include "KeyPair.h"

class User
{
public:
	User(std::string, std::string, KeyPair);
	User(std::string, std::string);
	~User() {};

	std::string		getName() const;
	std::string		getSurname() const;

	RSA::PublicKey getPublicKey() const;
	KeyPair			getKeyPair() const;
	RSA::PrivateKey getPrivateKey() const;

	std::string		toString() const;

private:
	std::string name;
	std::string surname;
	KeyPair keys;
};

