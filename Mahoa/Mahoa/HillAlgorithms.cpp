#include "HillAlgorithms.h"
#include <iostream>

#define NO_RESULT			 (-1)
#define MATRIX_SIZE			 3
#define NON_CHARACTER		(-1)
#define FAKE_CHARACTER		'O'

HillAlgorithms::HillAlgorithms()
{
	miIndex = NULL;
	miIndexDe = NULL;

	derCharacterFake[0] = 'A';
	derCharacterFake[1] = 'A';
	derCharacterFake[2] = 'A';

	

	mPlanText = "DEFAULT";
	mCipherText = "DEFAULT";

	int key[MATRIX_SIZE][MATRIX_SIZE] =
	{ { 2, 4, 5 },
	{ 9, 2, 1 },
	{ 3, 17, 7 } };

	insertKey(key);
	//EuclidExtended(383, 26);

	/*get det = 
	  a11 * a22 * a33  
	+ a12 * a23 * a31 
	+ a13 * a21 * a32
	- a13 * a22 * a31
	- a12 * a21 * a33
	- a11 * a23 * a32 */

	float det = mIKey[0][0] * mIKey[1][1] * mIKey[2][2] +
		mIKey[0][1] * mIKey[1][2] * mIKey[2][0] +
		mIKey[0][2] * mIKey[1][0] * mIKey[2][1]
		- mIKey[0][2] * mIKey[1][1] * mIKey[2][0]
		- mIKey[0][1] * mIKey[1][0] * mIKey[2][2]
		- mIKey[0][0] * mIKey[1][2] * mIKey[2][1];

	mInveMod26 = NO_RESULT;
	if (det != 0)
	 mInveMod26 = EuclidExtended(det, 26);

	if (mInveMod26 != -1)
	{
		mInvertKey[0][0] = (mIKey[1][1] * mIKey[2][2] - mIKey[2][1] * mIKey[1][2]) * mInveMod26;
		mInvertKey[0][1] = (-1) * (mIKey[0][1] * mIKey[2][2] - mIKey[2][1] * mIKey[0][2]) * mInveMod26;
		mInvertKey[0][2] = (mIKey[0][1] * mIKey[1][2] - mIKey[1][1] * mIKey[0][2]) * mInveMod26;

		mInvertKey[1][0] = (-1) * (mIKey[1][0] * mIKey[2][2] - mIKey[2][0] * mIKey[1][2]) * mInveMod26;
		mInvertKey[1][1] = (mIKey[0][0] * mIKey[2][2] - mIKey[2][0] * mIKey[0][2]) * mInveMod26;
		mInvertKey[1][2] = (-1) * (mIKey[0][0] * mIKey[1][2] - mIKey[1][0] * mIKey[0][2]) * mInveMod26;

		mInvertKey[2][0] = (mIKey[1][0] * mIKey[2][1] - mIKey[2][0] * mIKey[1][1]) * mInveMod26;
		mInvertKey[2][1] = (-1) * (mIKey[0][0] * mIKey[2][1] - mIKey[2][0] * mIKey[0][1]) * mInveMod26;
		mInvertKey[2][2] = (mIKey[0][0] * mIKey[1][1] - mIKey[1][0] * mIKey[0][1]) * mInveMod26;
	}

	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			while (mInvertKey[i][j] < 0)
				mInvertKey[i][j] += 26;
		}
	}

	//get mod 26
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
			mInvertKey[i][j] = (int)mInvertKey[i][j] % 26;
	}

	std::cout << "Ma tran chuyen vi theo modulo 26: " << std::endl;
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			std::cout << mInvertKey[i][j] << " ";
		}
		std::cout << std::endl;
	}

	//makeFakeCoupeCharater();
}


HillAlgorithms::~HillAlgorithms()
{
	if (miIndex)
		delete[]miIndex;
	
	if (miIndexDe)
		delete[]miIndexDe;
}

std::string HillAlgorithms::convertToEnCharacter(int a1, int a2, int a3)
{
	int q1, q2, q3;
	int a22 = a2, a33 = a3;

	if (a2 == NON_CHARACTER) a2 = 1;
	if (a3 == NON_CHARACTER) a3 = 1;

	q1 = (mIKey[0][0] * a1 + mIKey[0][1] * a2 + mIKey[0][2] * a3) % 26;
	q2 = (mIKey[1][0] * a1 + mIKey[1][1] * a2 + mIKey[1][2] * a3) % 26;
	q3 = (mIKey[2][0] * a1 + mIKey[2][1] * a2 + mIKey[2][2] * a3) % 26;

	std::string result;
	result += ZString[q1];

	if (a22 != NON_CHARACTER)
		result += ZString[q2];

	if (a33 != NON_CHARACTER)
		result += ZString[q3];

	return result;
}

std::string HillAlgorithms::convertToDeCharacter(int a1, int a2, int a3)
{
	int q1, q2, q3, a22 = a2, a33 = a3;

	if (a2 == NON_CHARACTER) a2 = 1;
	if (a3 == NON_CHARACTER) a3 = 1;

	q1 = (int)(mInvertKey[0][0] * a1 + mInvertKey[0][1] * a2 + mInvertKey[0][2] * a3) % 26;
	q2 = (int)(mInvertKey[1][0] * a1 + mInvertKey[1][1] * a2 + mInvertKey[1][2] * a3) % 26;
	q3 = (int)(mInvertKey[2][0] * a1 + mInvertKey[2][1] * a2 + mInvertKey[2][2] * a3) % 26;

	std::string result;
	result += ZString[q1];

	if (a22 != NON_CHARACTER)
		result += ZString[q2];

	if (a33 != NON_CHARACTER)
		result += ZString[q3];

	return result;
}

int HillAlgorithms::getIndex(char c)
{
	for (int i = 0; i < ZString.length(); i++)
		if (c == ZString[i])
			return i;

	return NO_RESULT;
}

std::string HillAlgorithms::Uppercase(std::string str)
{
	std::string result;


	for (int i = 0; i < str.length(); i++)
		if ((str[i] >= 'a' && str[i] < 'z'))
			result += str[i] - 32;
		else result += str[i];
		
		return result;
}

bool HillAlgorithms::isOnlyCharacter(std::string str)
{
	for (int i = 0; i < str.length(); i++)
		if ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z')) {
			continue;
		} else return false;

		return true;
}

void HillAlgorithms::Encrypt(std::string planText)
{
	isMakeKey = false;

	if (planText == "AAA")
		isMakeKey = true;
	else isMakeKey = false;

	if (!isMakeKey)
		std::cout << "Xau can ma hoa:" << planText << std::endl;

	if (!isOnlyCharacter(planText))
	{
		std::cout << "Thuat toan Hill chi ma hoa cho ky tu chu cai! Kiem tra lai xau dau vao." << std::endl;
		return;
	}

	if (mInveMod26 == NO_RESULT) {
		std::cout << " Khoa K khong ton tai ma tran kha nghich " << std::endl;
		return;
	}

	mPlanText = Uppercase(planText);

	int fakeCharacter = MATRIX_SIZE - mPlanText.length() % MATRIX_SIZE; // get mod MATRIX_SIZE for add block
	if (fakeCharacter == 3) fakeCharacter = 0;
	if (fakeCharacter != 0)
		for (int i = 0; i < fakeCharacter; i++)
			mPlanText += FAKE_CHARACTER;

	int textSize = mPlanText.length();
	miIndex = new int[textSize];

	for (int i = 0; i < textSize; i++) {
		*(miIndex + i) = getIndex(mPlanText[i]);
	}

	//encript
	mCipherText = "";

	for (int i = 0; i < textSize; i++) {
		if (i % MATRIX_SIZE == 0)
		{
			if (textSize - i >= MATRIX_SIZE)
				mCipherText += convertToEnCharacter(*(miIndex + i), *(miIndex + i + 1), *(miIndex + i + 2));
			/*else {
				if ((textSize - i) == 2)
					mCipherText += convertToEnCharacter(*(miIndex + i), *(miIndex + i + 1), NON_CHARACTER);
				else mCipherText += convertToEnCharacter(*(miIndex + i), NON_CHARACTER, NON_CHARACTER);
			}*/
		}
	}

	//remove fake encrypt character
	if (fakeCharacter != 0) {
		for (int i = 0; i < fakeCharacter; i++)
			derCharacterFake[i] = mCipherText[textSize - MATRIX_SIZE + i];

		mCipherText.erase(0, fakeCharacter);
	}

	if (!isMakeKey)
		std::cout << "Xau sau khi ma hoa:" << mCipherText << std::endl;
}

void HillAlgorithms::makeFakeCoupeCharater()
{
	Encrypt("anhyeuemnhieulam");
}

void HillAlgorithms::Decrypt(std::string cipherText)
{
	
	std::cout << "Xau can giai ma:" << cipherText << std::endl;

	if (cipherText.length() % 3) {
		std::cout << "Dau vao sai! Dau vao phai co do dai la boi so cua 3!" << std::endl;
		return;
	}

	if (!isOnlyCharacter(cipherText))
	{
		std::cout << "Thuat toan Hill chi ma hoa cho ky tu chu cai! Kiem tra lai xau dau vao." << std::endl;
		return;
	}

	if (mInveMod26 == NO_RESULT) {
		std::cout << " Khoa K khong ton tai ma tran kha nghich " << std::endl;
		return;
	}

	mCipherText = Uppercase(cipherText);

	/*int fakeCharacter = MATRIX_SIZE - cipherText.length() % MATRIX_SIZE;
	if (fakeCharacter != 0)
		for (int i = 0; i < fakeCharacter; i++)
			mCipherText += derCharacterFake[i];*/

	int textSize = mCipherText.length();
	miIndexDe = new int[textSize];

	for (int i = 0; i < textSize; i++) {
		*(miIndexDe + i) = getIndex(mCipherText[i]);
		//std::cout << "index = " << *(miIndexDe + i) << " ";
	}

	//decript
	mPlanText = "";

	for (int i = 0; i < textSize; i++) {
		if (i % 3 == 0)
		{
			if (textSize - i >= MATRIX_SIZE)
				mPlanText += convertToDeCharacter(*(miIndexDe + i), *(miIndexDe + i + 1), *(miIndexDe + i + 2));
		/*	else {
				if ((textSize - i) == 2)
					mPlanText += convertToDeCharacter(*(miIndexDe + i), *(miIndexDe + i + 1), NON_CHARACTER);
				else mPlanText += convertToDeCharacter(*(miIndexDe + i), NON_CHARACTER, NON_CHARACTER);
			}*/

			//mPlanText += convertToDeCharacter(*(miIndexDe + i), *(miIndexDe + i + 1), *(miIndexDe + i + 2));
		}
	}

	/*if (fakeCharacter != 0)
		mPlanText.erase(textSize - MATRIX_SIZE + fakeCharacter - 1, MATRIX_SIZE - fakeCharacter + 1);*/

		std::cout << "Xau sau khi giai ma:" << mPlanText << std::endl;
}

void HillAlgorithms::insertKey(const int key[3][3])
{
	std::cout << "Key = " << std::endl;

	for (int i = 0; i < 3; i++)  {
		for (int j = 0; j < 3; j++) {
			mIKey[i][j] = key[i][j];
			std::cout << mIKey[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

int HillAlgorithms::EuclidExtended(int a, int m)
{
	int ma = a, mm = m;
	int y0 = 0, y1 = 1;
	int r, q, y;

	while (a > 0)
	{
		r = m % a;
		if (r == 0) break;
		q = m / a;
		y = y0 - y1 * q;
		m = a;
		a = r;
		y0 = y1;
		y1 = y;
	}

	if (a > 1)
	{
		std::cout << a << " khong kha nghich theo modun " << m << std::endl;
		return 0;
	}
	else
	{
		while (y < 0)  y += mm;
		//std::cout << "Nghich dao modun " << mm << " cua " << ma << " la " << y << std::endl;
		return y;
	}
}