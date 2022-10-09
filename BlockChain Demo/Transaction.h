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

	User getUser() const;
	Message getMessage() const;
	string getHashTransaction() const;

private:
	User user;
	Message message;
	string hashTransaction;
};

