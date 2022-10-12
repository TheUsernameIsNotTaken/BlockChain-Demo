#include "Transaction.h"

//Create an user's message as a new transaction then hash it.
Transaction::Transaction(const User& _user, const Message& _message) :
	user(_user),
	message(_message)
{
	hashTransaction = SHA_256::sha256(_user.toString() + "_" + message.getMessage());
}

//!
//! \brief Check if a Transaction is correct. The identity name and surname should be enough long.
//!
//! \return :bool True if the transaction is correct
//!
bool Transaction::isCorrect() const
{
	if (user.getName().size() <= 1 && user.getSurname().size() <= 1)
		return false;

	if (message.getMessage().size() <= 1 ||
		message.getPublicKey().GetPublicExponent() != user.getPublicKey().GetPublicExponent() ||
		hashTransaction != SHA_256::sha256(user.toString() + "_" + message.getMessage()) ||
		!message.verifier()
		)
		return false;
	return true;
}

//A message's string form.
string Transaction::toString() const {
	string os;
	os += user.toString() + "_" + message.getMessage();
	return os;
}

//Returns the user.
User Transaction::getUser() const
{
	return user;
}
//Returns the mesaage.
Message Transaction::getMessage() const {
	return message;
}
//Returns the hash.
string Transaction::getHashTransaction() const {
	return hashTransaction;
}
