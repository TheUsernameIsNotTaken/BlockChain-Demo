#include "Transaction.h"

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


string Transaction::toString() const {
	string os;
	os += user.toString() + "_" + message.getMessage();
	return os;
}

User Transaction::getUser() const
{
	return user;
}
Message Transaction::getMessage() const {
	return message;
}
string Transaction::getHashTransaction() const {
	return hashTransaction;
}
