#include "Transaction.h"

Transaction::Transaction(User _user, string _message, int _amount) : 
	user(_user),
	to(_to),
	amount(_amount)
{
	from = _user.getName();
	hashTransaction = SHA_256::sha256(from + to + std::to_string(_amount));
}

Transaction::~Transaction()
{
}
