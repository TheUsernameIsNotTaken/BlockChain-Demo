#pragma once
#include <string>
#include "User.h"
#include "SHA_256.h"

using std::string;

class Transaction
{
public:
	Transaction(User, string, int);
	~Transaction();
private:
	User user;
	Message message;
	string hashTransaction;
};

