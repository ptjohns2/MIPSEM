#ifndef __PARSE_HPP__
#define __PARSE_HPP__

#include "types.hpp"

#include <string>
#include <vector>

using namespace std;


class parse{
	public:
		
		//Methods
		static string trimFront(string);
		static string trimEnd(string);
		static string trim(string);
		static string replaceChar(string str, char before, char after);

		static string sanitizeInstruction(string);
		static vector<string> tokenizeInstruction(string);
		
		static uint32_t binStrToUnsignedDecInt(string binStr);

		static char flipBit(char i);
		static string incBitStrByOne(string binStr);
		static string onesComplement(string binStr);
		static string twosComplement(string binStr);


		static bool argumentIsRegister(string argument);
		static bool argumentIsGPRegister(string argument);
		static bool argumentIsFPRegister(string argument);


		static string getGPRegisterName(int index);
		static string getFPRegisterName(int index);

		static int getRegisterIndex(string parameter);
		static int getGPRegisterIndex(string parameter);
		static int getFPRegisterIndex(string parameter);


		static bool tokenIsLiteral(string argument);
		static bool tokenIsDecimalLiteral(string argument);
		static bool tokenIsHexLiteral(string argument);
		static bool tokenIsBinaryLiteral(string argument);

		static int getLiteralValue(string argument);
		static int getDecimalLiteralValue(string argument);
		static int getHexLiteralValue(string argument);
		static int getBinaryLiteralValue(string argument);

		static int getArgumentValue(string argument);
		
		static string getValueDecimalLiteral(int val);
		static string getValueHexLiteral(int val);
		static string getValueBinaryLiteral(int val);

		static bool isDecimalDigit(char);
		static bool isHexDigit(char);
		static bool isBinaryDigit(char);
		
		static int decimalCharToDigit(char);
		static int hexCharToDigit(char);
		static int binaryCharToDigit(char);

		static bool hasParentheses(string);
		static string removeParentheses(string);


		//Members
		static string const GPRegisterNames[];
		static string const FPRegisterNames[];



	private:






};








#endif