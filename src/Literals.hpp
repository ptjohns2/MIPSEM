#ifndef __LITERALS_HPP__
#define __LITERALS_HPP__

#include "types.hpp"

#include <string>

using namespace std;

class Literals{
	public:
		Literals();
		~Literals();


		bool tokenIsLiteral(string);
		int getLiteralValue(string);
		
		static bool tokenIsDecimalLiteral(string);
		static bool isDecimalDigit(char);
		static int getDecimalDigitValue(char);
		static int getDecimalLiteralValue(string);
		static string getDecimalLiteralString(int);

		static bool tokenIsFloatLiteral(string);
		static float getFloatLiteralValue(string);
		static double getDoubleLiteralValue(string);
		static string getFloatLiteralString(float);
		static string getDoubleLiteralString(double);

		static bool tokenIsHexLiteral(string);
		static bool isHexDigit(char);
		static bool tokenIsRawHexLiteral(string);
		static int getHexDigitValue(char);
		static int getHexLiteralValue(string);
		static int getRawHexLiteralValue(string);
		static string getHexLiteralString(int);

		static bool tokenIsBinaryLiteral(string);
		static bool isBinaryDigit(char);
		static bool tokenIsRawBinaryLiteral(string);
		static int getBinaryDigitValue(char);
		static int getRawBinaryLiteralValue(string);
		static int getBinaryLiteralValue(string);
		static string getBinaryLiteralString(int);
		//utilities
		static uint32_t binStrToUnsignedDecInt(string binStr);
		static char flipBit(char i);
		static string incBitStrByOne(string binStr);
		static string onesComplement(string binStr);
		static string twosComplement(string binStr);

		static bool tokenIsOctalLiteral(string);
		static bool isOctalDigit(char);
		static bool tokenIsRawOctalLiteral(string);
		static int getOctalDigitValue(char);
		static int getRawOctalLiteralValue(string);
		static int getOctalLiteralValue(string);
		static string getOctalLiteralString(int);
		
		#define ESCAPED_RAW_CHAR_LITERAL_MIN_LENGTH 2
		#define ESCAPED_RAW_CHAR_LITERAL_MAX_LENGTH 4
		bool tokenIsCharLiteral(string);
		bool tokenIsRawCharLiteral(string);
		bool tokenIsRawEscapedCharLiteral(string);
		char getRawCharLiteralValue(string);
		char getRawEscapedCharLiteralValue(string);
		char getCharLiteralValue(string);
		string getCharLiteralString(char);

		bool tokenIsStringLiteral(string);
		bool tokenIsRawStringLiteral(string);
		string getRawStringLiteralValue(string);
		string getStringLiteralValue(string);
		string getStringLiteralString(string);

		
		#define NUM_CHARACTERS			256
		char EscapableCharacters[NUM_CHARACTERS];	//careful don't modify - can't be const
		
};


#endif