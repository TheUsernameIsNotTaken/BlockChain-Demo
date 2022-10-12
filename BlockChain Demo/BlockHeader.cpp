#include "BlockHeader.h"

//!
//! \brief Basic implementation of a BlockHeader 
//!							called when a Block is created
//!						The blockHeader is then further fulfill with 
//!						its correct value when the Merkle root tree has been build
//!						.. and the block has been mined
//!
//! \param : _numeroBloc The number of the Block
//! \return :
//!
BlockHeader::BlockHeader(int _blockNumber) :
	blockNumber(_blockNumber), merkleRootHash(""), timestamp(), nonce()
{
}

BlockHeader::~BlockHeader()
{
}

//!
//! \brief Implementation the equal operator
//!
//! \param : rhs 
//! \return :bool
//!
bool BlockHeader::operator==(const BlockHeader& rhs) const
{
	return (merkleRootHash == rhs.merkleRootHash && blockNumber == rhs.get_BlockNumber() && timestamp == rhs.get_Time());
}

void BlockHeader::setHashMerkleRoot(string hash) {
	merkleRootHash = hash;
}


void BlockHeader::setTime(std::chrono::milliseconds time) {
	timestamp = time;
}

superLong BlockHeader::get_Nonce() const
{
	return nonce;
}

int BlockHeader::get_BlockNumber() const {
	return blockNumber;
}
void BlockHeader::setNonce(superLong nce) {
	nonce = nce;
}
void BlockHeader::setNumero(int nmB) {
	blockNumber = nmB;
}

std::chrono::milliseconds BlockHeader::get_Time() const {
	return timestamp;
}
string BlockHeader::get_HashMerkleRoot() const {
	return merkleRootHash;
}
