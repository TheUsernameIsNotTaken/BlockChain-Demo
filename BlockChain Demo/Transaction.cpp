#include "Transaction.h"

Transaction::Transaction(User _user, Message _message) :
	user(_user),
	message(_message)
{
	hashTransaction = SHA_256::sha256(_user.toString() + "_" + message.getMessage());
}

Transaction::~Transaction()
{
}
