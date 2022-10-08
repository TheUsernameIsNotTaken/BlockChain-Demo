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

User::~User()
{
}


std::string User::getName() const
{
	return name;
}
std::string User::getSurname() const {
	return surname;
}

KeyPair User::getKeyPair() const
{
	return KeyPair();
}

std::string User::toString() const
{
	return getName() + " " + getSurname();
}