#include "Block.h"

//!
//! \brief Construct a fully correct Block with a reference to a previous one. Main Constructor
//! Construct a new Block, Build the header of the Block and also the Merkle Tree
//! \param : prevBloc A pointer to the previous Block
//! \param : _transaction A vector of transaction
//! \return :
//!
Block::Block(const ptr_Block& prevBloc, const vector<Transaction>& _transaction) :
	previousHash(prevBloc->currentHash), numOfTra(_transaction.size()), header(prevBloc->get_Header().get_NumeroBloc() + 1),
	transactions(), currentHash()
{

	// Copy the Hash of the Transactions
	for (auto t : _transaction)
	{
		transactions.emplace_back(t.getHashTransaction());
	}
	BuildMerkleRoot();

}

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
//! \brief Simple Constructor only used for Packet class. This constructs a semi valid Block,
//!		   The Block is not valid. Should not be used, unless when creating Packet
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

	if (numOfTra != transactions.size())
		return false;
	if (header.get_NumeroBloc() == 0)
		return true;
	if (SHA_256::sha256(string(header.get_HashMerkleRoot() + std::to_string(header.get_Nonce().first) + std::to_string(header.get_Nonce().second)))
		.substr(0, DIFFICULTY_MINING) != std::string(DIFFICULTY_MINING, '0'))
		return false;
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
		transactions.push_back(transactions.at(transactions.size() - 1)); numOfTra++;
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
	header.setTime(boost::posix_time::second_clock::local_time());

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

		string hash = SHA_256::sha256(string(header.get_HashMerkleRoot() + std::to_string(incr) + std::to_string(nonce)));
		if (hash.substr(0, DIFFICULTY_MINING) == sol)
			break;
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


void Block::set_Hash_Merkle_Root(string h)
{
	previousHash = h;
}


const BlockHeader& Block::get_Header() const
{
	return header;
}


string Block::get_PreviousBlockHash() const
{
	return previousHash;
}
string Block::get_BlockHash() const
{
	return currentHash;
}

const vector<string> Block::get_Transactions_List() const
{
	return transactions;
}

std::ostream& operator<<(std::ostream& os, const Block& p)
{
	os << std::endl;
	os << "***************************************************************************" << std::endl;
	os << "Bloc hash         : " << p.currentHash << std::endl;
	os << "Previous hash     : " << p.previousHash << std::endl;
	os << "Bloc number       : " << p.get_Header().get_NumeroBloc() << std::endl;
	os << "Nonce             : " << p.get_Header().get_Nonce().second << std::endl;
	os << "Time mined        : " << p.get_Header().get_Time() << std::endl;
	os << "Transaction list: " << std::endl;
	for (const auto& tr : p.get_Transactions_List())
	{
		std::cout << "    " << tr << std::endl;
	}
	os << "***************************************************************************" << std::endl;
	os << std::endl;
	return os;
}
