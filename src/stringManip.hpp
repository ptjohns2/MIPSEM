#ifndef __STRINGMANIP_HPP__
#define __STRINGMANIP_HPP__

#include <vector>
#include <string>
#include "types.hpp"


using namespace std;

class stringManip{
	public:
		static string trimFront(string);
		static string trimEnd(string);
		static string trim(string);
		static int contains(string, string);
		static string replaceChar(string str, char before, char after);

		static string sanitizeInstruction(string);
		static vector<string> tokenizeInstruction(string);
		
		static int binStrToSignedDecInt(string binStr);
		static instr binStrToDecInt(string binStr);
		static string decIntToBinStr(int val);

		static char flipBit(char i);
		static string incBitStrByOne(string binStr);
		static string onesComplement(string binStr);
		static string twosComplement(string binStr);
	private:


};












#endif