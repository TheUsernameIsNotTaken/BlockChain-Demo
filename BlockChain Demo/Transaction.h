#pragma once
#include <string>
#include "User.h"
#include "SHA_256.h"
#include "Message.h"

using std::string;

class Transaction
{
public:
	//Transaction() : user(), message(), hashTransaction() {};
	Transaction(const User&, const Message&);
	~Transaction() {};

	bool isCorrect() const;
	string toString() const;

	bool operator==(const Transaction& tr)
	{
		return (tr.user.getName() == user.getName() &&
			tr.hashTransaction == hashTransaction &&
			tr.message.getMessage() == message.getMessage());
	}
	bool operator<(const Transaction& tr) const
	{
		return hashTransaction < tr.getHashTransaction();
	}

	User getUser() const;
	Message getMessage() const;
	string getHashTransaction() const;

private:
	User user;
	Message message;
	string hashTransaction;
};

