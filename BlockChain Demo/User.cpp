#include "User.h"

User::User(std::string _name, std::string _surname, KeyPair _keys) :
	name(_name),
	surname(_surname),
	keys(_keys)
{

}

User::User(std::string _name, std::string _surname) :
	name(_name),
	surname(_surname)
{
	keys = KeyPair();
}


std::string User::getName() const
{
	return name;
}
std::string User::getSurname() const {
	return surname;
}

RSA::PublicKey User::getPublicKey() const {
	return keys.getPublicKey();
}
KeyPair User::getKeyPair() const {
	return keys;

}
RSA::PrivateKey User::getPrivateKey() const {
	return keys.getPrivateKey();
}

std::string User::toString() const
{
	return getName() + " " + getSurname();
}
