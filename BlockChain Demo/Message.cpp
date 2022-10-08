#include "Message.h"

Message::Message(string _information, KeyPair _keys) :
	message(_information),
	publicKey(_keys.getPublicKey()),
	messageSize(message.size())
{

}

//Getters
string Message::getMessage() const
{
	return message;
}
RSA::PublicKey Message::getPublicKey() const
{
	return publicKey;
}

bool Message::verifier() const
{
	//Declare the used objects
	CryptoPP::RSASSA_PKCS1v15_SHA_Verifier verifier(publicKey);
	//Verify the message
	return verifier.VerifyMessage((const byte*)message.c_str(), message.length(), signature, signature.size());
}

SecByteBlock Message::sign(RSA::PrivateKey& pk)
{
	//Declare the used objects
	CryptoPP::AutoSeededRandomPool rng;
	CryptoPP::RSASSA_PKCS1v15_SHA_Signer signer(pk);
	size_t length = signer.MaxSignatureLength();
	signature = SecByteBlock(length);

	//Sign the message
	length = signer.SignMessage(rng, (const byte*)message.c_str(), message.length(), signature);
	signature.resize(length);
	signature = SecByteBlock(signature.data(), signature.size());
	return signature;
}