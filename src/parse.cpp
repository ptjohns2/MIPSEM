#include "parse.hpp"

#include "types.hpp"

#include <bitset>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

string parse::trimFront(string str){
	if(str == ""){return "";}
	int len = str.length();
	int i = 0;
	while((str[i] == ' ' || str[i] == '\t') && i < len){
		i++;
	}

	return str.substr(i);
}

string parse::trimEnd(string str){
	if(str == ""){return "";}
	int len = str.length();
	int i = len - 1;
	while((str[i] == ' ' || str[i] == '\t') && i > -1){
		i--;
	}
	i++;

	return str.substr(0, i);
}

string parse::trim(string str){
	return trimEnd(trimFront(str));
	/*
	str = trimEnd(str);
	str = trimFront(str);
	return str;
	*/
}

string parse::replaceChar(string str, char before, char after){
	for(int i=0; i<str.length(); i++){
		if(str[i] == before){
			str[i] = after;
		}
	}
	return str;
}

string parse::sanitizeInstruction(string str){
	int i = 0;
	int len = str.length();
	while(i<len && str[i] != '#'){
		if(str[i] == '\t'){str[i] = ' ';}
		i++;
	}
	string substr = str.substr(0, i);
	return trim(substr);
}

vector<string> parse::tokenizeInstruction(string str){
	// NAME A1,A2,A3,A4#xxxx
	str = sanitizeInstruction(str);

	string beforeParen;
	string afterParen;

	stringstream ss(str);
	getline(ss, beforeParen, '(');
	getline(ss, afterParen);
	if(afterParen.length() != 0){
		afterParen = "(" + afterParen;
	}

	vector<string> tokens;

	//get arguments from beforeParen
	stringstream ssBeforeParen(beforeParen);
	string tmpStr;
	getline(ssBeforeParen, tmpStr, ' ');	//get instruction name
	tokens.push_back(trim(tmpStr));
	while(getline(ssBeforeParen, tmpStr, ',')){
		tokens.push_back(trim(tmpStr));
	}

	//get arguments from afterParen
	if(afterParen.length() != 0){
		stringstream ssAfterParen(afterParen);
		while(getline(ssAfterParen, tmpStr, ',')){
			tokens.push_back(trim(tmpStr));
		}
	}
	return tokens;
}

int32_t parse::binStrToSignedDecInt(string binStr){
	bool isNeg = (binStr[0] == '1');
	if(isNeg){
		binStr = twosComplement(binStr);
	}
	bitset<INSTRUCTIONSIZE> tmpBitset = bitset<INSTRUCTIONSIZE>(binStr);
	int retVal = (int)(tmpBitset.to_ulong());

	if(isNeg){
		retVal = -1 * retVal;
	}
	return retVal;
}

uint32_t parse::binStrToUnsignedDecInt(string binStr){
	bitset<INSTRUCTIONSIZE> tmpBitset = bitset<INSTRUCTIONSIZE>(binStr);
	uint32_t retVal = (uint32_t)(tmpBitset.to_ulong());
	return retVal;
}

string parse::decIntToBinStr(int32_t val){
	bool isNeg = (val < 0);
	if(isNeg){
		val = -1 * val;
	}
	bitset<INSTRUCTIONSIZE> tmpBitset = bitset<INSTRUCTIONSIZE>(val);
	string binStr = tmpBitset.to_string();
	if(isNeg){
		binStr = twosComplement(binStr);
	}
	return binStr;
}

char parse::flipBit(char i){
	if(i == '0'){
		return '1';
	}else{
		return '0';
	}
}

string parse::incBitStrByOne(string binStr){
	int i = binStr.length()-1;
	char lastChar = binStr[i];
	if(lastChar == '1'){
		while(binStr[i] == '1'){
			binStr[i] = '0';
			i--;
		}
		binStr[i] = '1';
	}else{
		binStr[i] = '1';
	}

	return binStr;
}

string parse::onesComplement(string binStr){
	for(int i=0; i<binStr.length(); i++){
		binStr[i] = flipBit(binStr[i]);
	}
	return binStr;
}

string parse::twosComplement(string binStr){
	binStr = onesComplement(binStr);
	binStr = incBitStrByOne(binStr);

	return binStr;
}




