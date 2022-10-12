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
		Block mineBlock(string prevHash, BlockHeader h, vector<string> HashVector){
			Block newBlock(prevHash, HashVector.size(), HashVector, h);
			newBlock.solveProofofWork();
			return newBlock;
		}
		TEST_METHOD(TestBlockMining_1)
		{
			//Arrange
			//Users
			User u1(name, surname, kp);
			User u2("Elemer", "Elmeno");
			User u3("Mordor", "Mormol");
			User u4("Steve", "Elive");
			User u5("Eline", "Ms. Dog");
			//Messages
			Message m1(info, kp);
			Message m2("Üdvözletem mindenkinek!", u2.getKeyPair());
			Message m3("Hello guyz and galz!", u3.getKeyPair());
			Message m4("WHYYYYYYYYYY??????", u4.getKeyPair());
			Message m5("Why not?", u3.getKeyPair());
			Message m6("My dog just just texted me it's over... :(", u4.getKeyPair());
			Message m7("What did I do wrong, that she just leaves me.", u4.getKeyPair());
			Message m8("I even feed her like 2 times every day... :(", u4.getKeyPair());
			Message m9("Sorry my firend!", u2.getKeyPair());
			Message m10("Stop Spamming u3, or BAN!", u1.getKeyPair());
			Message m11("Yeah, but you're never home STEVE!", u5.getKeyPair());
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
			Transaction t6(u4, m6);
			string t6Hash = t6.getHashTransaction();
			Transaction t7(u4, m7);
			string t7Hash = t7.getHashTransaction();
			Transaction t8(u4, m8);
			string t8Hash = t8.getHashTransaction();
			Transaction t9(u2, m9);
			string t9Hash = t9.getHashTransaction();
			Transaction t10(u1, m10);
			string t10Hash = t10.getHashTransaction();
			Transaction t11(u5, m11);
			string t11Hash = t11.getHashTransaction();
			//Act
			//Initialize new Chain
			Block b0 = Block(0);
			//Build-a-Block - test 1
			vector<string> HashVector{ t1Hash, t2Hash, t3Hash, t4Hash };
			Block b1 = mineBlock(b0.get_BlockHash(), BlockHeader(1), HashVector);
			//Build-a-Block - test 2
			vector<string> HashVector_2{ t3Hash, t5Hash };
			Block b2 = mineBlock(b1.get_BlockHash(), BlockHeader(2), HashVector_2);
			//Build-a-Block - test 3
			vector<string> HashVector_3{ t6Hash, t7Hash, t8Hash };
			Block b3 = mineBlock(b2.get_BlockHash(), BlockHeader(3), HashVector_3);
			//Build-a-Block - test 4
			vector<string> HashVector_4{ t9Hash, t10Hash, t11Hash };
			Block b4 = mineBlock(b3.get_BlockHash(), BlockHeader(4), HashVector_4);
			//Assert
			//Correction			
			//Valid messages
			Assert::IsTrue(m1.verifier(), L"Unvalid message 1", LINE_INFO());
			Assert::IsTrue(m2.verifier(), L"Unvalid message 2", LINE_INFO());
			Assert::IsTrue(m3.verifier(), L"Unvalid message 3", LINE_INFO());
			Assert::IsTrue(m4.verifier(), L"Unvalid message 4", LINE_INFO());
			Assert::IsTrue(m5.verifier(), L"Unvalid message 5", LINE_INFO());
			Assert::IsTrue(m6.verifier(), L"Unvalid message 6", LINE_INFO());
			Assert::IsTrue(m7.verifier(), L"Unvalid message 7", LINE_INFO());
			Assert::IsTrue(m8.verifier(), L"Unvalid message 8", LINE_INFO());
			Assert::IsTrue(m9.verifier(), L"Unvalid message 9", LINE_INFO());
			Assert::IsTrue(m10.verifier(), L"Unvalid message 10", LINE_INFO());
			Assert::IsTrue(m11.verifier(), L"Unvalid message 11", LINE_INFO());
			//Transaction correction
			Assert::IsTrue(PARITY_TRANSACTION.isCorrect(), L"Uncorrect parity transaction", LINE_INFO());
			Assert::IsTrue(t1.isCorrect(), L"Uncorrect transaction 1", LINE_INFO());
			Assert::IsTrue(t2.isCorrect(), L"Uncorrect transaction 2", LINE_INFO());
			Assert::IsTrue(t3.isCorrect(), L"Uncorrect transaction 3", LINE_INFO());
			Assert::IsTrue(t4.isCorrect(), L"Uncorrect transaction 4", LINE_INFO());
			Assert::IsTrue(t5.isCorrect(), L"Uncorrect transaction 5", LINE_INFO());
			Assert::IsTrue(t6.isCorrect(), L"Uncorrect transaction 6", LINE_INFO());
			Assert::IsTrue(t7.isCorrect(), L"Uncorrect transaction 7", LINE_INFO());
			Assert::IsTrue(t8.isCorrect(), L"Uncorrect transaction 8", LINE_INFO());
			Assert::IsTrue(t9.isCorrect(), L"Uncorrect transaction 9", LINE_INFO());
			Assert::IsTrue(t10.isCorrect(), L"Uncorrect transaction 10", LINE_INFO());
			Assert::IsTrue(t11.isCorrect(), L"Uncorrect transaction 11", LINE_INFO());
			//Block values
			std::stringstream ss;
			ss << b0 << std::endl << b1 << std::endl << b2 << std::endl << b3 << std::endl << b4 << std::endl;
			Logger::WriteMessage(ss.str().c_str());
			ss.clear();
			////Block Validity
			Assert::IsTrue(b0.isValid(), L"Unvalid block 0", LINE_INFO());
			Assert::IsTrue(b1.isValid(), L"Unvalid block 1", LINE_INFO());
			Assert::IsTrue(b2.isValid(), L"Unvalid block 2", LINE_INFO());
			Assert::IsTrue(b3.isValid(), L"Unvalid block 3", LINE_INFO());
			Assert::IsTrue(b4.isValid(), L"Unvalid block 4", LINE_INFO());
			////Same block test
			Assert::IsTrue(b0 == b0, L"Not equal same blocks 0", LINE_INFO());
			Assert::IsTrue(b1 == b1, L"Not equal same blocks 1", LINE_INFO());
			Assert::IsTrue(b2 == b2, L"Not equal same blocks 2", LINE_INFO());
			Assert::IsTrue(b1 == b1, L"Not equal same blocks 3", LINE_INFO());
			Assert::IsTrue(b2 == b2, L"Not equal same blocks 4", LINE_INFO());
		}
	};
}
