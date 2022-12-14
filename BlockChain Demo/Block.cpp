#include "Block.h"

//!
//! \brief Construct a Block without no reference to the previous one. Should be used with precautions
//!
//! \param : previousBlockHash the previous Block Hash
//! \param : nbtransaction the number of transactions in the new block
//! \param : tr The transactions
//! \param : _header A Header 
//! \return :
//!
Block::Block(string previousBlockHash, int nbtransaction, vector<string> tr, const BlockHeader _header) :
	previousHash(previousBlockHash), numOfTra(nbtransaction),
	transactions(tr), header(_header), currentHash()
{
	BuildMerkleRoot();
}


//!
//! \brief Simple Constructor only used for Starting a blockchain. This constructs a semi valid Block,
//!		   The Block is not valid. Should not be used, unless when creating a chain.
//! \param : p 
//! \return :
//!
Block::Block(int p) :
	previousHash(), currentHash(FIRST_BLOCK_HASH), numOfTra(0), header(0), transactions()
{

}

Block::~Block()
{
}

//!
//! \brief Copy Constructor
//!
//! \param : rhs 
//! \return :Block::Block&
//!
Block& Block::operator=(Block rhs)
{
	if (rhs == *this)
		return *this;
	header = rhs.header;
	previousHash = rhs.previousHash;
	currentHash = rhs.currentHash;
	numOfTra = rhs.numOfTra;
	transactions.clear();
	transactions = rhs.transactions;
	return *this;
}

bool Block::operator==(const Block& rhs) const
{
	return (header == rhs.get_Header() && transactions == rhs.transactions
		&& previousHash == rhs.get_PreviousBlockHash() && numOfTra == rhs.numOfTra);
}



//!
//! \brief Check if the block is valid, all the transaction added to a Block should always be verified ! Because at the end
//!					the block keep only a hash of the transaction
//! \return :bool
//!
bool Block::isValid() const
{
	//Check if no transaction was added
	if (numOfTra != transactions.size())
		return false;
	//Pass, if it is the header block. - It's value will never be processed.
	if (header.get_BlockNumber() == 0)
		return true;
	//Check if PoW hash is correct.
	if (SHA_256::sha256(string(std::to_string(header.get_Time().count()) + 
		std::to_string(header.get_Nonce().first) + std::to_string(header.get_Nonce().second) + 
		header.get_HashMerkleRoot() + previousHash))
		.substr(0, DIFFICULTY_MINING) != std::string(DIFFICULTY_MINING, '0'))
		return false;

	//Double transaction check - Bug: If I copy the last transaction, for parity, then it is wrong. -> Change it.
	//Added parity transaction as debug.
	std::vector<string> tr_buf = transactions;
	std::sort(tr_buf.begin(), tr_buf.end());
	if (std::unique(tr_buf.begin(), tr_buf.end()) != tr_buf.end())
		return false;

	return true;
}



//!
//! \brief Build the Merkle Tree of the Block. Update the Header consequently
//!
//! \return :void
//!
void Block::BuildMerkleRoot()
{
	// To get a even number of transactions
	if (transactions.size() & 1) {
		transactions.push_back(PARITY_TRANSACTION.getHashTransaction());
		numOfTra++;
	}
	int N = transactions.size();

	vector<string> hashTree;
	hashTree.resize(2 * N - 1);
	for (int i = 0; i < N; i++)
		hashTree.at(2 * N - 2 - i) = transactions.at(i);
	for (int i = N - 2; i > -1; i--)
	{
		hashTree.at(i) = SHA_256::sha256(SHA_256::sha256(hashTree.at(2 * i + 1) + hashTree.at(2 * i + 2)));
	}

	header.setHashMerkleRoot(hashTree.at(0));
	//Update timestamp
	std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch()
		);
	header.setTime(ms);
	//Update Hash
	currentHash = SHA_256::sha256(SHA_256::sha256(header.get_HashMerkleRoot()));
}

//!
//! \brief Find a nonce that will solve the Proof the Work. See proof of Work for more information
//! \brief The difficulty can be set in the Constante file
//! \return :paire Return the nonce
//!
superLong Block::solveProofofWork()
{
	unsigned long long nonce = 0, incr = 0;
	unsigned long long const limit = std::numeric_limits<unsigned long long>::max();

	string sol(DIFFICULTY_MINING, '0');
	while (true) {

		string hash = SHA_256::sha256(string(
			std::to_string(header.get_Time().count()) + 
			std::to_string(incr) + std::to_string(nonce) + 
			header.get_HashMerkleRoot() + previousHash));
		if (hash.substr(0, DIFFICULTY_MINING) == sol)
		{
			currentHash = hash;
			break;
		}
		else
			++nonce;
		if (limit - 1 == nonce) // Increment the incr when nonce reach unsigned long long int max value
		{
			incr++;
			nonce = 0;
		}
	}
	header.setNonce(superLong(incr, nonce));

	return superLong(incr, nonce);
}

//! \brief Check if a Transaction is in the Block
//!
//! \param : tr
//! \return :bool Return true if the transaction is in the Block
//!
bool Block::containsTransactions(const Transaction& tr) const
{
	// There is an actually improvement possible with the Merkle Root but it isn't implemented yet
	return (std::find(transactions.begin(), transactions.end(), tr.getHashTransaction()) != transactions.end());
}

//Update the previous Hash.
void Block::update_PreviousHash(string h)
{
	previousHash = h;
}

//Returns header.
const BlockHeader& Block::get_Header() const
{
	return header;
}

//Returns Prevoius Block's Hash.
string Block::get_PreviousBlockHash() const
{
	return previousHash;
}
//Returns the Block's Hash.
string Block::get_BlockHash() const
{
	return currentHash;
}
//Return the transaction Hash List.
const vector<string> Block::get_Transactions_List() const
{
	return transactions;
}

//The Block's data in string.
std::ostream& operator<<(std::ostream& os, const Block& p)
{
	os << std::endl;
	os << "***************************************************************************" << std::endl;
	os << "Bloc hash         : " << p.currentHash << std::endl;
	os << "Previous hash     : " << p.previousHash << std::endl;
	os << "Bloc number       : " << p.get_Header().get_BlockNumber() << std::endl;
	os << "Nonce             : " << p.get_Header().get_Nonce().second << std::endl;
	os << "Time mined        : " << p.get_Header().get_Time().count() << std::endl;
	os << "Transaction list: " << std::endl;
	for (auto& tra : p.get_Transactions_List())
	{
		os << "		" << tra << std::endl;
	}
	os << "***************************************************************************" << std::endl;
	os << std::endl;
	return os;
}
