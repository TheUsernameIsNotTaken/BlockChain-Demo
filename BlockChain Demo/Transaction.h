#pragma once
#include <string>
#include "User.h"
#include "SHA_256.h"
#include "Message.h"

using std::string;

class Transaction
{
public:
	Transaction(User, Message);
	~Transaction();
private:
	User user;
	Message message;
	string hashTransaction;
};

