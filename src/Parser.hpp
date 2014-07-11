#ifndef __ParseR_HPP__
#define __ParseR_HPP__

#include "types.hpp"

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;


class Parser{
	public:
		Parser();
		~Parser();
		
		//Methods
		static string trimFront(string);
		static string trimEnd(string);
		static string trim(string);
		static string replaceChar(string str, char before, char after);

		static bool hasParentheses(string);
		static string removeParentheses(string);

		static bool hasTrailingComma(string);
		static string removeTrailingComma(string);

		static bool isWhiteSpace(char);
		static string sanitizeInstruction(string);
		static vector<string> tokenizeInstruction(string);
		static vector<string> stringExplode(string);
		static vector<string> stringExplodeAndSanitize(string);

		static uint32_t binStrToUnsignedDecInt(string binStr);

		static char flipBit(char i);
		static string incBitStrByOne(string binStr);
		static string onesComplement(string binStr);
		static string twosComplement(string binStr);

		



		int getArgumentValue(string argument);


		bool tokenIsRegister(string token);
		bool tokenIsGPRegister(string token);
		bool tokenIsFPRegister(string token);

		static string getGPRegisterName(int index);
		static string getFPRegisterName(int index);

		int getRegisterIndex(string token);
		int getGPRegisterIndex(string token);
		int getFPRegisterIndex(string token);


		static bool tokenIsLiteral(string argument);
		static bool tokenIsDecimalLiteral(string argument);
		static bool tokenIsHexLiteral(string argument);
		static bool tokenIsBinaryLiteral(string argument);

		static int getLiteralValue(string argument);
		static int getDecimalLiteralValue(string argument);
		static int getHexLiteralValue(string argument);
		static int getBinaryLiteralValue(string argument);

		static string getValueDecimalLiteral(int val);
		static string getValueHexLiteral(int val);
		static string getValueBinaryLiteral(int val);


		bool tokenIsDirective(string token);
		int getDirectiveNumber(string token);



		static bool isDecimalDigit(char);
		static bool isHexDigit(char);
		static bool isBinaryDigit(char);
		
		static int decimalCharToDigit(char);
		static int hexCharToDigit(char);
		static int binaryCharToDigit(char);


		//Members
		#define NUM_GP_REGISTER_NAMES 64
		#define NUM_FP_REGISTER_NAMES 32
		#define NUM_DIRECTIVE_NAMES 20
		static string const GPRegisterNames[];
		static string const FPRegisterNames[];
		static string const DirectiveNames[];
		unordered_map<string, int> GPRegisterNameMap;
		unordered_map<string, int> FPRegisterNameMap;
		unordered_map<string, int> DirectiveNameMap;


	private:






};








#endif