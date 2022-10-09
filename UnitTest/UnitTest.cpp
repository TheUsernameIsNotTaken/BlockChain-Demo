#include "pch.h"
#include "CppUnitTest.h"
#include <iostream>
#include "../BlockChain Demo/Transaction.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(UnitTests)
	{
	public:
		//Test under-block level classes.
		//Arrange for all.
		KeyPair kp = KeyPair();
		std::string name = "Pista";
		std::string surname = "Kiss";
		std::string info = "Drága barátaim!";
		TEST_METHOD(TestUser)
		{
			//Arrange
			User u = User(name, surname, kp);
			const std::string toStr = name + " " + surname;
			//Act
			Logger::WriteMessage(("Publikus kulcs: " + 
				std::to_string(kp.getPublicKey().GetPublicExponent().ConvertToLong()) + " | " +
				std::to_string(kp.getPublicKey().GetModulus().ConvertToLong()) + "\n").c_str());
			Logger::WriteMessage(("Privát kulcs: " + 
				std::to_string(kp.getPrivateKey().GetPrivateExponent().ConvertToLong()) + "\n").c_str());
			//Assert
			Assert::AreEqual(u.toString(), toStr, L"Changed name", LINE_INFO());
			Assert::AreEqual(u.getPrivateKey().GetPrivateExponent().ConvertToLong(), kp.getPrivateKey().GetPrivateExponent().ConvertToLong(), L"Changed privet key", LINE_INFO());
			Assert::AreEqual(u.getPublicKey().GetPublicExponent().ConvertToLong(), kp.getPublicKey().GetPublicExponent().ConvertToLong(), L"Changed public key", LINE_INFO());
		}
		TEST_METHOD(TestMessage)
		{
			//Arrange
			Message m(info, kp);
			//Act
			bool verified = m.verifier();
			string to1 = m.getMessage();
			//Assert
			Assert::AreEqual(to1, info, L"Changed Message", LINE_INFO());
			Assert::IsTrue(verified, L"Not verified", LINE_INFO());
		}
		TEST_METHOD(TestTransaction)
		{
			//Arrange
			User u(name, surname, kp);
			Message m(info, kp);
			Transaction t(u, m);
			string toStr = name + " " + surname + "_" + info;
			//Actbool verified = m.verifier();
			bool isCorr = t.isCorrect();
			string CurrHash = SHA_256::sha256(toStr);
			//Assert
			Assert::AreEqual(t.getUser().toString(), u.toString(), L"Changed User", LINE_INFO());
			Assert::AreEqual(t.getMessage().getMessage(), m.getMessage(), L"Changed Message", LINE_INFO());
			Assert::AreEqual(t.toString(), toStr, L"Wrong toString()", LINE_INFO());
			Assert::AreEqual(t.getHashTransaction(), CurrHash, L"Different hashes", LINE_INFO());
			Assert::IsTrue(isCorr, L"Uncorrect transaction", LINE_INFO());

		}
	};
}
