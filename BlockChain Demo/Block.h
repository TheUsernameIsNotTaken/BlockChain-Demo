#pragma once
#include <memory>
#include <iostream>
#include <string>
#include <vector>
#include "BlockHeader.h"
#include "Transaction.h"

static int DIFFICULTY_MINING = 4;
static std::string FIRST_BLOCK_HASH = "0000f671bf37164c071d526e8960fd9122383d5d73ef3b60f1bc9f330a15c1e1";

using std::vector;


class Block
{	
	using ptr_Block = std::shared_ptr<Block>;
public:
	explicit Block(int);
	Block(const ptr_Block&, const vector<Transaction>&);
	Block(string, int, vector<string>, const BlockHeader);
	Block() = delete;

	void set_Hash_Merkle_Root(string);

	~Block();

	Block& operator=(Block);
	bool operator==(const Block&) const;

	const vector<string> get_Transactions_List() const;
	const BlockHeader& get_Header() const;
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