#include "User.h"

//Declare an user with a specific name and KeyPair.
User::User(std::string _name, std::string _surname, const KeyPair& _keys) :
	name(_name),
	surname(_surname),
	keys(_keys)
{

}

//Declare an user with a specific name. Also generates a new KeyPair for the user.
User::User(std::string _name, std::string _surname) :
	name(_name),
	surname(_surname)
{
	keys = KeyPair();
}

//Returns the name.
std::string User::getName() const
{
	return name;
}
//Returns the surname.
std::string User::getSurname() const {
	return surname;
}

//Returns the Public Key.
RSA::PublicKey User::getPublicKey() const {
	return keys.getPublicKey();
}
//Returns the KeyPair.
KeyPair User::getKeyPair() const {
	return keys;

}
//Returns the Private Key.
RSA::PrivateKey User::getPrivateKey() const {
	return keys.getPrivateKey();
}

//Generates the USer's name as a single string.
std::string User::toString() const
{
	return getName() + " " + getSurname();
}

//!
//! \brief 
//!
//! \param : os 
//! \return :std::ostream&
//!
std::ostream& User::operator<<(std::ostream& os) {
	os << name << " " << surname << std::endl;
	return os;
}