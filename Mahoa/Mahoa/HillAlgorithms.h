#pragma once
#include <string>

class HillAlgorithms
{
private:
	std::string ZString = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	std::string mPlanText;
	std::string mCipherText;
	int mIKey[3][3];
	float mInvertKey[3][3];
	int *miIndex;
	int *miIndexDe;
	int mInveMod26;
	char derCharacterFake[3];
	void makeFakeCoupeCharater();
	bool isMakeKey;
private:
	void insertKey(const int key[3][3]);
	int getIndex(char c);
	bool isOnlyCharacter(std::string str);
	std::string Uppercase(std::string str);
	std::string convertToEnCharacter(int a1, int a2, int a3);
	std::string convertToDeCharacter(int a1, int a2, int a3);
	int EuclidExtended(int a, int m);
public:
	HillAlgorithms();
	~HillAlgorithms();
	void Encrypt(std::string planText);
	void Decrypt(std::string cipherText);
	
	
	
	

};

