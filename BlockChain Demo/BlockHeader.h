#pragma once
#include <stdint.h>
#include <string>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/time_serialize.hpp>

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
	void setNumero(int);
	void setHashMerkleRoot(string);
	void setTime(boost::posix_time::ptime);

	boost::posix_time::ptime get_Time() const;
	string					 get_HashMerkleRoot() const;
	int						 get_NumeroBloc() const;
	superLong				 get_Nonce()	const;
private:
	int blockNumber;
	boost::posix_time::ptime timestamp;
	superLong nonce;
	string merkleRootHash;
};
