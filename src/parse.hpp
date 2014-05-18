#ifndef __PARSE_HPP__
#define __PARSE_HPP__

#include "types.hpp"

#include <string>
#include <vector>

using namespace std;

class parse{
	public:
		static string trimFront(string);
		static string trimEnd(string);
		static string trim(string);
		static string replaceChar(string str, char before, char after);

		static string sanitizeInstruction(string);
		static vector<string> tokenizeInstruction(string);
		
		static int32_t binStrToSignedDecInt(string binStr);
		static uint32_t binStrToUnsignedDecInt(string binStr);
		static string decIntToBinStr(int32_t val);

		static char flipBit(char i);
		static string incBitStrByOne(string binStr);
		static string onesComplement(string binStr);
		static string twosComplement(string binStr);
	private:


};












#endif