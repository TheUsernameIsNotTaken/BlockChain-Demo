#pragma once
#include <string>
#include "sha.h"
#include "hex.h"
using std::string;
using namespace CryptoPP;

class SHA_256
{
public:
	static string sha256(string message) {
		SHA256 hash;
		byte digest[SHA256::DIGESTSIZE];
		hash.CalculateDigest(digest, (byte*)message.c_str(), message.length());

		HexEncoder encoder;
		string sha;
		encoder.Attach(new StringSink(sha));
		encoder.Put(digest, sizeof(digest));
		encoder.MessageEnd();
		return sha;
	}
};
