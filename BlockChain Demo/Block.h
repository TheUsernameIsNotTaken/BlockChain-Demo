#pragma once
#include <memory>
#include <iostream>
#include <string>
#include <vector>
#include "BlockHeader.h"
#include "Transaction.h"

static int DIFFICULTY_MINING = 4;
static std::string FIRST_BLOCK_HASH = "0000F671BF37164C071D526E8960FD9122383D5D73EF3B60F1BC9F330A15C1E1";

using std::vector;


class Block
{
public:
	explicit Block(int);
	Block(string, int, vector<string>, const BlockHeader);
	Block() = delete;

	void update_PreviousHash(string);

	~Block();

	Block& operator=(Block);
	bool operator==(const Block&) const;

	const vector<string> get_Transactions_List() const;
	const BlockHeader&   get_Header() const;
	string			     get_PreviousBlockHash() const;
	string			     get_BlockHash() const;


	bool		isValid() const;
	bool		containsTransactions(const Transaction&) const;
	superLong	solveProofofWork();

	friend std::ostream& operator<<(std::ostream& os, const Block& p);
private:
	string currentHash;
	string previousHash;
	
	BlockHeader header;
	int numOfTra;
	
	vector<string> transactions;
	void BuildMerkleRoot();

};