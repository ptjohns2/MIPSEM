#include "parse.hpp"

#include <bitset>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <sstream>

//	public Methods


string parse::trimFront(string str){
	if(str == ""){return "";}
	int len = str.length();
	int i = 0;
	while((str[i] == ' ' || str[i] == '\t') && i < len){
		i++;
	}
	if((i == len-1) && (str[i] == '\t' || str[i] == '\t')){return "";}
	return str.substr(i);
}

string parse::trimEnd(string str){
	if(str == ""){return "";}
	int len = str.length();
	int i = len - 1;
	while((str[i] == ' ' || str[i] == '\t') && i > -1){
		i--;
	}
	if((i == 0) && (str[i] == ' ' || str[i] == '\t')){return "";}
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
	for(unsigned int i=0; i<str.length(); i++){
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

	stringstream ss(str);

	vector<string> tokensBeforeParenSplit;
	vector<string> tokensAfterParenSplit;

	//tokenize instructions without splitting parenthises
	string tmpStr;
	getline(ss, tmpStr, ' ');	//get instruction name
	tokensBeforeParenSplit.push_back(trim(tmpStr));
	while(getline(ss, tmpStr, ',')){
		tokensBeforeParenSplit.push_back(trim(tmpStr));
	}
	ss.clear();
	//split tokens by parenthises
	for(unsigned int i=0; i<tokensBeforeParenSplit.size(); i++){
		stringstream ss(tokensBeforeParenSplit[i]);
		string beforeParen, afterParen;
		getline(ss, beforeParen, '(');
		getline(ss, afterParen);
		tokensAfterParenSplit.push_back(beforeParen);
		if(afterParen.length() != 0){
			tokensAfterParenSplit.push_back("(" + afterParen);
		}
	}
	
	return tokensAfterParenSplit;
}


uint32_t parse::binStrToUnsignedDecInt(string binStr){
	bitset<INSTRUCTIONSIZE> tmpBitset = bitset<INSTRUCTIONSIZE>(binStr);
	uint32_t retVal = (uint32_t)(tmpBitset.to_ulong());
	return retVal;
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
	for(unsigned int i=0; i<binStr.length(); i++){
		binStr[i] = flipBit(binStr[i]);
	}
	return binStr;
}

string parse::twosComplement(string binStr){
	binStr = onesComplement(binStr);
	binStr = incBitStrByOne(binStr);

	return binStr;
}









bool parse::argumentIsRegister(string argument){
	return argumentIsGPRegister(argument) || argumentIsFPRegister(argument);
}
bool parse::argumentIsGPRegister(string argument){
	return getGPRegisterIndex(argument) != -1;
}
bool parse::argumentIsFPRegister(string argument){
	return getFPRegisterIndex(argument) != -1;
}



string parse::getGPRegisterName(int index){
	assert(index >= 0 && index < 32);
	return GPRegisterNames[index];
}
string parse::getFPRegisterName(int index){
	assert(index >= 0 && index < 32);
	return FPRegisterNames[index];
}


int parse::getRegisterIndex(string argument){
	if(argumentIsGPRegister(argument)){
		return getGPRegisterIndex(argument);
	}else if(argumentIsFPRegister(argument)){
		return getFPRegisterIndex(argument);
	}
	cout << "error parse::getRegisterIndex - invalid argument";
	getchar();
	return 0;
}

//TODO: memoize the get*RegisterIndex functions
int parse::getGPRegisterIndex(string argument){
	if(argument[0] != '$'){return -1;}
	if(argument.length() > 5){return -1;}
	bool isNumericRegister = true;
	for(unsigned int i=1; i<argument.length()-1; i++){
		isNumericRegister &= isDecimalDigit(argument[i]);
	}
	if(isNumericRegister){
		int regNum = atoi(argument.substr(1).c_str());
		if(regNum >= 0 && regNum <= 31){
			return regNum;
		}else{
			return -1;
		}
	}else{
		for(int i=0; i<=31; i++){
			if(argument == GPRegisterNames[i]){
				return i;
			}
		}
	}
	return -1;
}

int parse::getFPRegisterIndex(string argument){
	if(argument[0] != '$'){return -1;}
	if(argument.length() > 4){return -1;} 
	for(unsigned int i=2; i<argument.length()-1; i++){
		if(!isDecimalDigit(argument[i])){return -1;}
	}
	int regNum = atoi(argument.substr(1).c_str());
	if(regNum >= 0 && regNum <= 31){
		return regNum;
	}
	return -1;
}



bool parse::tokenIsLiteral(string argument){
	return tokenIsDecimalLiteral(argument)
		|| tokenIsHexLiteral(argument)
		|| tokenIsBinaryLiteral(argument);
}
bool parse::tokenIsDecimalLiteral(string argument){
	int start = 0;
	if(argument[0] == '-'){start++;}
	for(unsigned int i=start; i<argument.length(); i++){
		if(!isDecimalDigit(argument[i])){return false;}
	}
	return true;
}
bool parse::tokenIsHexLiteral(string argument){
	if(argument[0] != '0'){return false;}
	if(argument[1] != 'x'){return false;}
	if(argument.length() > 10){return false;}
	for(unsigned int i=2; i<argument.length(); i++){
		if(!isHexDigit(argument[i])){return false;}
	}
	return true;
}
bool parse::tokenIsBinaryLiteral(string argument){
	if(argument[0] != '0'){return false;}
	if(argument[1] != 'b'){return false;}
	if(argument.length() > 34){return false;}
	for(unsigned int i=2; i<argument.length(); i++){
		if(!isBinaryDigit(argument[i])){return false;}
	}
	return true;
}


int parse::getLiteralValue(string argument){
	if(tokenIsDecimalLiteral(argument)){
		return getDecimalLiteralValue(argument);
	}else if(tokenIsHexLiteral(argument)){
		return getHexLiteralValue(argument);
	}else if(tokenIsBinaryLiteral(argument)){
		return getBinaryLiteralValue(argument);
	}
	cout << "error[int getLiteralValue(string argument)]: " << argument << " is not a valid literal value\n";
	getchar();
	return 0;
}
int parse::getDecimalLiteralValue(string argument){
	bool isNeg = argument[0] == '-';
	int start = isNeg? 1 : 0;
	int retVal = 0;
	for(unsigned int i=start; i<argument.length(); i++){
		retVal *= 10;
		retVal += decimalCharToDigit(argument[i]);
	}
	if(isNeg){retVal *= -1;}
	return retVal;
}
int parse::getHexLiteralValue(string argument){
	int retVal = 0;
	for(unsigned int i=2; i<argument.length(); i++){
		retVal <<= 4;
		retVal |= hexCharToDigit(argument[i]);
	}
	return retVal;
}
int parse::getBinaryLiteralValue(string argument){
	//this instead of binStrToSigned/UnsignedDecInt(string binStr)
	//	so it's counted as leading 0s
	int retVal = binStrToUnsignedDecInt(argument.substr(2));
	return retVal;
}



int parse::getArgumentValue(string argument){
	argument = removeParentheses(argument);
	if(argumentIsRegister(argument)){
		return getRegisterIndex(argument);
	}else if(tokenIsLiteral(argument)){
		return getLiteralValue(argument);
	}
	cout << "Error invalid token " << argument << '\n';
	getchar();
	return 0;
}

string parse::getValueDecimalLiteral(int val){
	return std::to_string(val);
}
string parse::getValueHexLiteral(int val){
	stringstream ss;
	ss << "0x" << std::setw(8) << std::setfill('0') << std::hex << val;
	return ss.str();
}
string parse::getValueBinaryLiteral(int val){
	bool isNeg = (val < 0);
	if(isNeg){
		val = -1 * val;
	}
	bitset<INSTRUCTIONSIZE> tmpBitset = bitset<INSTRUCTIONSIZE>(val);
	string binStr = tmpBitset.to_string();
	if(isNeg){
		binStr = twosComplement(binStr);
	}
	return "0b" + binStr;
}


//
bool parse::isDecimalDigit(char c){
	return (c >= '0' && c <= '9');
}
bool parse::isHexDigit(char c){
	return (c >= '0' && c <= '9')
		|| (c >= 'a' && c <= 'f')
		|| (c >= 'A' && c <= 'F');
}
bool parse::isBinaryDigit(char c){
	return c == '0' || c == '1';
}

int parse::decimalCharToDigit(char c){
	return c - '0';
}
int parse::hexCharToDigit(char c){
	if(c >= '0' && c <= '9'){return c - '0';}
	else if(c >= 'a' && c <= 'f'){return c - 'a' + 10;}
	else if(c >= 'A' && c <= 'F'){return c - 'A' + 10;}
	//error, not real hex char
	return 0;
}
int parse::binaryCharToDigit(char c){
	return (c == '0')? 0 : 1;
}

bool parse::hasParentheses(string str){
	return str[0] == '(' && str[str.length()-1] == ')';
}

string parse::removeParentheses(string str){
	if(hasParentheses(str)){
		str = str.substr(1, str.length() - 1 - 1);	//1 for each parentheses
	}
	return str;
}

//	Members
std::string const parse::GPRegisterNames[] = {
	"$zero",
	"$at",
	"$v0", "$v1",
	"$a0", "$a1", "$a2", "$a3",
	"$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7",
	"$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7",
	"$t8", "$t9",
	"$k0", "$k1",
	"$gp",
	"$sp",
	"$fp",
	"$ra"
};

std::string const parse::FPRegisterNames[] = {
	"$f0", "$f1", "$f2", "$f3", "$f4", "$f5", "$f6", "$f7",
	"$f8", "$f9", "$f10", "$f11", "$f12", "$f13", "$f14", "$f15",
	"$f16", "$f17", "$f18", "$f19", "$f20", "$f21", "$f22", "$f23",
	"$f24", "$f25", "$f26", "$f27", "$f28", "$f29", "$f30", "$f31"
};
