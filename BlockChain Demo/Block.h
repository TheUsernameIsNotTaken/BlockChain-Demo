#include <string>
#include <vector>

using std::string;
using std::vector;

class Block
{
public:
	Block();
	~Block() {};
private:
	vector<string> transactions;
	void BuildMerkleRoot();

	int numOfTra;
	int id;

	string hash;
	string prevHash;
	time_t timestamp;
};