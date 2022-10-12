#pragma once
#include <stdint.h>
#include <string>
#include <chrono>

using std::string;
using superLong = std::pair<unsigned long long, unsigned long long>;

class BlockHeader
{
public:
	BlockHeader(int);

	BlockHeader() = delete;
	~BlockHeader();

	bool operator==(const BlockHeader&) const;

	void setNonce(superLong);
	void setBlockNumber(int);
	void setHashMerkleRoot(string);
	void setTime(std::chrono::milliseconds);

	std::chrono::milliseconds get_Time() const;
	string					  get_HashMerkleRoot() const;
	int						  get_BlockNumber() const;
	superLong				  get_Nonce()	const;
private:
	int blockNumber;
	std::chrono::milliseconds timestamp;
	superLong nonce;
	string merkleRootHash;
};
