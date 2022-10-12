#include "Message.h"

//Create a new message by giving all information, then signing it.
Message::Message(string _information, const KeyPair& _keys) :
	message(_information),
	publicKey(_keys.getPublicKey()),
	messageSize(message.size())
{
	sign(_keys.getPrivateKey());
}

//Get message
string Message::getMessage() const
{
	return message;
}
//Get the public key to check signature.
RSA::PublicKey Message::getPublicKey() const
{
	return publicKey;
}

//Check if the digital signature is correct.
bool Message::verifier() const
{
	//Declare the used objects
	CryptoPP::RSASSA_PKCS1v15_SHA_Verifier verifier(publicKey);
	//Verify the message
	return verifier.VerifyMessage((const byte*)message.c_str(), message.length(), signature, signature.size());
}

//Do the digital signature.
SecByteBlock Message::sign(RSA::PrivateKey pk)
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