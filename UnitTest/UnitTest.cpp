#include "pch.h"
#include "CppUnitTest.h"
#include <iostream>
#include "../BlockChain Demo/Transaction.h"
#include "../BlockChain Demo/Block.h"

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
		TEST_METHOD(TestBlockMining)
		{
			//Arrange
			//Users
			User u1(name, surname, kp);
			User u2("Elemer", "Elmeno");
			User u3("Steve", "Elive");
			User u4("Mordor", "Mormol");
			//Messages
			Message m1(info, kp);
			Message m2("Üdvözletem mindenkinek!", u2.getKeyPair());
			Message m3("Hello guyz and galz!", u3.getKeyPair());
			Message m4("WHYYYYYYYYYY??????", u4.getKeyPair());
			Message m5("Why not?", u3.getKeyPair());
			//Transactions
			Transaction t1(u1, m1);
			string t1Hash = t1.getHashTransaction();
			Transaction t2(u2, m2);
			string t2Hash = t2.getHashTransaction();
			Transaction t3(u3, m3);
			string t3Hash = t3.getHashTransaction();
			Transaction t4(u4, m4);
			string t4Hash = t4.getHashTransaction();
			Transaction t5(u3, m5);
			string t5Hash = t5.getHashTransaction();
			//Act
			//Initialize new Chain
			Block b0 = Block(0);
			//Build-a-Block - test 1
			BlockHeader bh1(1);
			vector<string> HashVector{ t1Hash, t2Hash, t3Hash, t4Hash };
			Block b1(b0.get_BlockHash(), 4, HashVector, bh1);
			b1.solveProofofWork();
			////Build-a-Block - test 2
			//auto b0_ptr = std::shared_ptr<Block>(&b0);
			//vector<Transaction> TVector{ t1, t2, t3, t4 };
			//Block b1_v2(b0_ptr, TVector);
			//Build-a-Block - test 3
			BlockHeader bh2(2);
			vector<string> HashVector_2{ t3Hash, t5Hash };
			Block b2(b1.get_BlockHash(), 2, HashVector_2, bh2);
			b2.solveProofofWork();
			////Build-a-Block - test 4
			//auto b1_ptr = std::shared_ptr<Block>(&b1);
			//vector<Transaction> TVector_2{ t3, t5 };
			//Block b2_v2(b1_ptr, TVector_2);
			//Assert
			//Correction			
			//Valid messages
			Assert::IsTrue(m1.verifier(), L"Unvalid message 1", LINE_INFO());
			Assert::IsTrue(m2.verifier(), L"Unvalid message 2", LINE_INFO());
			Assert::IsTrue(m3.verifier(), L"Unvalid message 3", LINE_INFO());
			Assert::IsTrue(m4.verifier(), L"Unvalid message 4", LINE_INFO());
			Assert::IsTrue(m5.verifier(), L"Unvalid message 5", LINE_INFO());
			//Transaction correction
			Assert::IsTrue(t1.isCorrect(), L"Uncorrect transaction 1", LINE_INFO());
			Assert::IsTrue(t2.isCorrect(), L"Uncorrect transaction 2", LINE_INFO());
			Assert::IsTrue(t3.isCorrect(), L"Uncorrect transaction 3", LINE_INFO());
			Assert::IsTrue(t4.isCorrect(), L"Uncorrect transaction 4", LINE_INFO());
			Assert::IsTrue(t5.isCorrect(), L"Uncorrect transaction 5", LINE_INFO());
			////Block Validity
			Assert::IsTrue(b1.isValid(), L"Unvalid block 1", LINE_INFO());
			Assert::IsTrue(b2.isValid(), L"Unvalid block 2", LINE_INFO());
			//Block values
			std::stringstream ss;
			ss << b1 << std::endl << std::endl << b2 << std::endl << std::endl;
			Logger::WriteMessage(ss.str().c_str());
			////Same block test
			Assert::IsTrue(b1 == b1, L"Not equal same blocks 1", LINE_INFO());
			Assert::IsTrue(b2 == b2, L"Not equal same blocks 2", LINE_INFO());
		}
	};
}
