#include "stringManip.hpp"
#include "types.hpp"

#include <iostream>
#include <sstream>
#include <vector>
#include <bitset>

using namespace std;

string stringManip::trimFront(string str){
	if(str == ""){return "";}
	int len = str.length();

	int i = 0;
	while((str[i] == ' ' || str[i] == '\t') && i < len){
		i++;
	}

	return str.substr(i, len);
}

string stringManip::trimEnd(string str){
	if(str == ""){return "";}
	int len = str.length();
	int i = len - 1;
	while((str[i] == ' ' || str[i] == '\t') && i > -1){
		i--;
	}
	i++;

	return str.substr(0, i);
}

string stringManip::trim(string str){
	string retVal = trimEnd(str);
	retVal = trimFront(retVal);
	return retVal;
}

int stringManip::contains(string str, string chars){
	for(int i=0; i<str.length(); i++){
		for(int j=0; j<chars.length(); j++){
			if(str[i] == chars[j]){
				return i;
			}
		}
	}
	return -1;
}

string stringManip::replace(string str, char before, char after){
	for(int i=0; i<str.length(); i++){
		if(str[i] == before){
			str[i] = after;
		}
	}
	return str;
}

string stringManip::sanitizeInstruction(string str){
	int i = 0;
	int len = str.length();
	while(i<len && str[i] != '#'){
		if(str[i] == '\t'){
			str[i] = ' ';
		}
		i++;
	}
	//if(i==len){i--;}

	return str.substr(0, i);
}


vector<string> stringManip::tokenizeInstruction(string str){
	// NAME A1,A2,A3,A4#xxxx
	str = sanitizeInstruction(str);
	str = trim(str);
	vector<string> tokens;
	stringstream ss(str);
	string tmpStr;
	getline(ss, tmpStr, ' ');	//get instruction name
	tokens.push_back(trim(tmpStr));

	//get arguments
	while(getline(ss, tmpStr, ',')){
		tokens.push_back(trim(tmpStr));
	}
	return tokens;
}




int stringManip::binStrToSignedDecInt(string binStr){
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


instr stringManip::binStrToDecInt(string binStr){
	bitset<INSTRUCTIONSIZE> tmpBitset = bitset<INSTRUCTIONSIZE>(binStr);
	instr retVal = (instr)(tmpBitset.to_ulong());
	return retVal;
}


string stringManip::decIntToBinStr(int val){
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


char stringManip::flipBit(char i){
	if(i == '0'){
		return '1';
	}else{
		return '0';
	}
}

string stringManip::incBitStrByOne(string binStr){
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

string stringManip::onesComplement(string binStr){
	for(int i=0; i<binStr.length(); i++){
		binStr[i] = flipBit(binStr[i]);
	}
	return binStr;
}

string stringManip::twosComplement(string binStr){
	binStr = onesComplement(binStr);
	binStr = incBitStrByOne(binStr);

	return binStr;
}




