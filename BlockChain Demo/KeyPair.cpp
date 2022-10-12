#include "KeyPair.h"

//Declare a NEW Key pair, by generating a new Private and Public key pair. Uses CryptoPP library.
KeyPair::KeyPair() :
	publicKey(), privateKey()
{
	CryptoPP::AutoSeededRandomPool rng;

	CryptoPP::InvertibleRSAFunction parameters;
	parameters.GenerateRandomWithKeySize(rng, SIZE_KEY);
	publicKey = RSA::PublicKey(parameters);
	privateKey = RSA::PrivateKey(parameters);
}

//Declare keypair as a copy of an other keypair.
KeyPair::KeyPair(const KeyPair& _keys) :
	publicKey(_keys.publicKey), privateKey(_keys.privateKey)
{
}

//Declare a keypair by using a specific Private and Public key.
KeyPair::KeyPair(const RSA::PublicKey& _publicKey, const RSA::PrivateKey& _privateKey) :
	publicKey(_publicKey),
	privateKey(_privateKey)
{
}

//Set the private key of the pair.
void KeyPair::setPrivateKey(const RSA::PrivateKey& sk)
{
	privateKey = sk;
}
//Set the public key of the pair.
void KeyPair::setPublicKey(const RSA::PublicKey& pk) {
	publicKey = pk;
}

//Returns the public key.
RSA::PublicKey KeyPair::getPublicKey() const
{
	return publicKey;
}
//Returns the private key.
RSA::PrivateKey KeyPair::getPrivateKey() const
{
	return privateKey;
}

//Encrypt a message using the KeyPair. Returns the chipper. Uses CryptoPP's RSA algorithm.
string KeyPair::encrypt(string message) {
	using namespace CryptoPP;
	AutoSeededRandomPool rng;
	string cipher;
	RSAES_OAEP_SHA_Encryptor e(publicKey);
	try {
		StringSource ss(message, true,
			new PK_EncryptorFilter(rng, e,
				new StringSink(cipher)
			)
		);
	}
	catch (std::exception e) {
		std::cerr << "Encryption error!";
	}

	return cipher;
}

//Decrypt a chipper using the KeyPair. Returns the message. Uses CryptoPP's RSA algorithm.
string KeyPair::decrypt(string cipher) {
	using namespace CryptoPP;
	AutoSeededRandomPool rng;
	string pl_text;
	try {
		RSAES_OAEP_SHA_Decryptor d(privateKey);
		StringSource(cipher, true,
			new PK_DecryptorFilter(rng, d,
				new StringSink(pl_text)
			)
		);
	}
	catch (...) {
		throw "Decryption error!";
	}

	return	pl_text;
}

////Saving a key to file
//void KeyPair::Save(const string& filename, const CryptoPP::BufferedTransformation& bt)
//{
//	CryptoPP::FileSink file(filename.c_str());
//
//	bt.CopyTo(file);
//	file.MessageEnd();
//
//}
//
//void KeyPair::savePrivateKey(const string& filename, const RSA::PrivateKey& key)
//{
//	CryptoPP::ByteQueue queue;
//	key.Save(queue);
//	Save(filename, queue);
//}
//
//void KeyPair::savePublicKey(const string& filename, const RSA::PublicKey& key) {
//	CryptoPP::ByteQueue queue;
//	key.Save(queue);
//	Save(filename, queue);
//}
//
////Loading back
//void KeyPair::Load(const string& filename, CryptoPP::BufferedTransformation& bt)
//{
//
//	try {
//		CryptoPP::FileSource file(filename.c_str(), true /*pumpAll*/);
//		file.TransferTo(bt);
//		bt.MessageEnd();
//	}
//	catch (CryptoPP::FileSource::Err e)
//	{
//		return;
//	}
//	catch (...)
//	{
//		throw CryptoPP::FileSource::Err::INVALID_ARGUMENT;
//	}
//
//}
//
//bool KeyPair::loadPrivateKey(const string& filename, RSA::PrivateKey& key)
//{
//	try {
//		CryptoPP::ByteQueue queue;
//		Load(filename, queue);
//		key.Load(queue);
//		return true; // TODO
//	}
//	catch (std::exception e)
//	{
//		return false;
//	}
//	catch (...)
//	{
//		return false;
//	}
//}
//
//bool KeyPair::loadPublicKey(const string& filename, RSA::PublicKey& key)
//{
//	try {
//		CryptoPP::ByteQueue queue;
//		Load(filename, queue);
//		key.Load(queue);
//		return true; // TODO
//	}
//	catch (std::exception e)
//	{
//		return false;
//	}
//	catch (...)
//	{
//		return false;
//	}
//}